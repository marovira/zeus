#include <zeus/filesystem.hpp>

#include <catch2/catch.hpp>

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
#if defined(ZEUS_PLATFORM_WINDOWS)
    std::string expected{"\\path\\to\\file"};
#else
    std::string expected{"/path/to/file"};
#endif
    auto result = get_file_directory(file_path);
    REQUIRE(result == expected);
}
