c="C:/deps"
if(-not (Test-Path $c))
{
    python .github/workflows/scripts/generate_versions.py

    # Read necessary versions.
    $catch_ver = Get-Content $env:USERPROFILE\zeus_catch_version.txt
    $fmt_ver = Get-Content $env:USERPROFILE\zeus_fmt_version.txt
    $me_ver = Get-Content $env:USERPROFILE\zeus_magic_enum_version.txt

    git clone https://github.com/Neargye/magic_enum --branch v$me_ver --depth 1
    cmake -G "Visual Studio 17 2022" -S magic_enum -B magic_enum/build -DCMAKE_CXX_STANDARD=20 -DMAGIC_ENUM_OPT_BUILD_EXAMPLES=OFF -DMAGIC_ENUM_OPT_INSTALL=ON -DMAGIC_ENUM_OPT_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=C:/deps/magic_enum
    cd ./magic_enum/build
    cmake --build . --config $env:BUILD_TYPE
    cmake --build . --target INSTALL --config $env:BUILD_TYPE
    cd ../..

    git clone https://github.com/fmtlib/fmt.git --branch $fmt_ver --depth 1
    cmake -G "Visual Studio 17 2022" -S fmt -B fmt/build -DCMAKE_CXX_STANDARD=20 -DFMT_INSTALL=ON -DFMT_TEST=OFF -DCMAKE_INSTALL_PREFIX=C:/deps/fmt
    cd ./fmt/build
    cmake --build . --config $env:BUILD_TYPE
    cmake --build . --target INSTALL --config $env:BUILD_TYPE
    cd ../..

    git clone https://github.com/catchorg/Catch2.git --branch v$catch_ver --depth 1
    cmake -G "Visual Studio 17 2022" -S Catch2 -B Catch2/build -DCMAKE_CXX_STANDARD=20 -DCATCH_INSTALL_DOCS=OFF -DCMAKE_INSTALL_PREFIX=C:/deps/Catch2
    cd ./Catch2/build
    cmake --build . --config $env:BUILD_TYPE
    cmake --build . --target INSTALL --config $env:BUILD_TYPE
    cd ../..
}
