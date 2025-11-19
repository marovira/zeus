import argparse
import dataclasses as dc
import json
import os
import pathlib
import platform
import shutil
import stat
import subprocess
import typing


@dc.dataclass
class SDKInfo:
    url: str = ""
    tag: str = ""
    tag_prefix: str = ""
    flags: list[str] = dc.field(default_factory=list)
    cmake_var: str = ""


DEPENDENCIES: dict[str, SDKInfo] = {
    "magic_enum": SDKInfo(
        url="https://github.com/Neargye/magic_enum.git",
        tag_prefix="v",
        flags=[
            "-DMAGIC_ENUM_OPT_BUILD_EXAMPLES=OFF",
            "-DMAGIC_ENUM_OPT_INSTALL=ON",
            "-DMAGIC_ENUM_OPT_BUILD_TESTS=OFF",
        ],
        cmake_var="ZEUS_MAGIC_ENUM_VERSION",
    ),
    "fmt": SDKInfo(
        url="https://github.com/fmtlib/fmt.git",
        flags=[
            "-DFMT_INSTALL=ON",
            "-DFMT_TEST=OFF",
        ],
        cmake_var="ZEUS_FMT_VERSION",
    ),
    "Catch2": SDKInfo(
        url="https://github.com/catchorg/Catch2.git",
        tag_prefix="v",
        flags=[
            "-DCATCH_INSTALL_DOCS=OFF",
        ],
        cmake_var="ZEUS_CATCH_VERSION",
    ),
}


@dc.dataclass
class CMakeConfig:
    generator: str = ""
    cxx_standard: str = ""

    def get_generator_flags(self) -> list[str]:
        return ["-G", self.generator]

    def get_cxx_standard_flag(self) -> str:
        return f"-DCMAKE_CXX_STANDARD={self.cxx_standard}"


def rmtree_error(func, path, exc_info):
    if not os.access(path, os.W_OK):
        os.chmod(path, stat.S_IWUSR)  # noqa: PTH101
        func(path)
    else:
        raise exc_info


def find_preset(presets: list[dict[str, typing.Any]], name: str) -> dict[str, typing.Any]:
    for preset in presets:
        if preset["name"] == name:
            return preset

    raise KeyError(f"error: CMakePresets file does not contain a preset called {name}")


def get_cmake_config(project_root: pathlib.Path) -> CMakeConfig:
    preset_path = project_root / "CMakePresets.json"
    with preset_path.open("rb") as infile:
        preset_data = json.load(infile)

        presets = preset_data["configurePresets"]
        config = CMakeConfig()
        if platform.system() == "Windows":
            base_preset = find_preset(presets, "msvc")
        else:
            base_preset = find_preset(presets, "unix_base")

        config.generator = base_preset["generator"]
        config.cxx_standard = base_preset["cacheVariables"]["CMAKE_CXX_STANDARD"]

        return config


def execute_command(proc_name: str, args: list[str]) -> None:
    try:
        env = os.environ.copy()
        subprocess.run(args, check=True, env=env)
    except subprocess.CalledProcessError as exc:
        raise RuntimeError(f"{proc_name} finised with a non-zero exit code") from exc


def clone_repo(name: str, info: SDKInfo) -> None:
    args = ["git", "clone", info.url, name, "--branch", info.tag, "--depth", "1"]
    execute_command(f"Cloning {name}", args)


def configure_cmake(
    name: str,
    sdk_info: SDKInfo,
    cmake_cfg: CMakeConfig,
    build_root: pathlib.Path,
    install_root: pathlib.Path,
) -> None:
    args = ["cmake"]
    args.extend(cmake_cfg.get_generator_flags())
    args.extend(
        ["-S", name, "-B", f"{str(build_root)}", cmake_cfg.get_cxx_standard_flag()]
    )
    args.extend(sdk_info.flags)
    args.append(f"-DCMAKE_INSTALL_PREFIX={str(install_root)}")
    args.append("-DCMAKE_DEBUG_POSTFIX=d")

    execute_command(f"Configuring {name}", args)


def build(name: str, build_root: pathlib.Path, config: str) -> None:
    assert config in (None, "Debug", "Release")

    args = ["cmake", "--build", f"{str(build_root)}", "--parallel", "--config", config]
    execute_command(f"Building {name}", args)


def install(name: str, build_root: pathlib.Path, config: str) -> None:
    assert config in (None, "Debug", "Release")

    args = ["cmake", "--install", f"{str(build_root)}", "--config", config]
    execute_command(f"Installing {name}", args)


def check_dependencies(deps_root: pathlib.Path) -> bool:
    installed_deps = [folder.stem for folder in deps_root.iterdir() if folder.is_dir()]
    return all(name in installed_deps for name in DEPENDENCIES)


def install_dependencies(
    cmake_cfg: CMakeConfig, deps_root: pathlib.Path, config: str
) -> None:
    if check_dependencies(deps_root):
        return

    existing_deps = [
        dir_name.stem for dir_name in deps_root.iterdir() if dir_name.is_dir()
    ]

    src_root = deps_root / "src"

    if src_root.exists():
        shutil.rmtree(src_root, onerror=rmtree_error)
    src_root.mkdir(exist_ok=True, parents=True)

    cur_dir = pathlib.Path.cwd()
    os.chdir(src_root)

    for name, info in DEPENDENCIES.items():
        if name in existing_deps:
            continue

        clone_repo(name, info)

        build_root = src_root / (name + "/build")
        configure_cmake(name, info, cmake_cfg, build_root, deps_root / name)
        build(name, build_root, config)
        install(name, build_root, config)

    os.chdir(cur_dir)
    shutil.rmtree(src_root, onerror=rmtree_error)


def read_versions(root: pathlib.Path) -> None:
    deps_file = root / "dependencies.txt"

    with deps_file.open("r", encoding="utf-8") as infile:
        lines = infile.read().splitlines()

    for line in lines:
        if "#" in line:
            continue

        elems = line.split("==")
        for sdk in DEPENDENCIES.values():
            if sdk.cmake_var == elems[0]:
                sdk.tag = sdk.tag_prefix + elems[1]


def main() -> None:
    parser = argparse.ArgumentParser(
        description="Automated dependency build script for Zeus"
    )
    parser.add_argument(
        "root",
        metavar="ROOT",
        type=str,
        nargs=1,
        help="The root where the dependencies will be built",
    )
    parser.add_argument(
        "build",
        metavar="BUILD",
        type=str,
        nargs=1,
        help="Build configuration to use. Must be one of 'Debug' or 'Release'",
    )

    args = parser.parse_args()

    deps_root = pathlib.Path(args.root[0]).resolve()
    config = args.build[0]

    project_root = pathlib.Path(__file__).parent.parent

    read_versions(project_root)
    cmake_cfg = get_cmake_config(project_root)

    deps_root.mkdir(exist_ok=True, parents=True)
    install_dependencies(cmake_cfg, deps_root, config)


if __name__ == "__main__":
    main()
