#include <zeus/filesystem.hpp>

#include <catch2/catch_test_macros.hpp>
#include <string>

TEST_CASE("[filesystem] - get_file_directory: no root")
{
    using zeus::get_file_directory;

    const std::string file_path{"file.txt"};
    auto result = get_file_directory(file_path);
    REQUIRE(result == "");
}

TEST_CASE("[filesystem] - get_file_directory: valid root")
{
    using zeus::get_file_directory;

    const std::string file_path{"/path/to/file/name.txt"};
    std::string expected{"/path/to/file"};
    auto result = get_file_directory(file_path);
    REQUIRE(result == expected);
}

TEST_CASE("[filesystem] - ChdirScope")
{
    using zeus::ChdirScope;
    namespace fs = zeus::zeus_fs;

    const auto start_path = fs::current_path();
    const auto new_path   = start_path / "test_dir";
    auto cur_path         = start_path;
    fs::create_directory(new_path);
    REQUIRE(fs::exists(new_path));
    REQUIRE(cur_path == start_path);

    {
        const auto _ = ChdirScope{new_path};
        cur_path     = fs::current_path();
        REQUIRE(cur_path == new_path);
    }

    cur_path = fs::current_path();
    REQUIRE(cur_path == start_path);

    fs::remove(new_path);
}
