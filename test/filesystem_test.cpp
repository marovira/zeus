#include <zeus/filesystem.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("[filesystem] - get_file_directory: no root")
{
    using zeus::get_file_directory;

    std::string file_path{"file.txt"};
    auto result = get_file_directory(file_path);
    REQUIRE(result == "");
}

TEST_CASE("[filesystem] - get_file_directory: valid root")
{
    using zeus::get_file_directory;

    std::string file_path{"/path/to/file/name.txt"};
    std::string expected{"/path/to/file"};
    auto result = get_file_directory(file_path);
    REQUIRE(result == expected);
}
