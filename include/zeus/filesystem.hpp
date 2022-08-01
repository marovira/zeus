#pragma once

#include "platform.hpp"

#include <fmt/printf.h>

#if defined(ZEUS_PLATFORM_WINDOWS)
#    define _SILENCE_EXPERIMENTAL_FILESYSTEM_DEPRECATION_WARNING
#endif
#include <experimental/filesystem>
#include <string>

namespace zeus
{
    inline std::time_t get_file_last_write(std::string filename)
    {
        namespace fs = std::experimental::filesystem;

        fs::path file_path{filename};
        [[maybe_unused]] std::error_code code;
        auto ftime = fs::last_write_time(file_path, code);
        if (code && current_build == BuildType::debug)
        {
            fmt::print(stderr, "warning: ({}): {}\n", code.value(), code.message());
        }

        return decltype(ftime)::clock::to_time_t(ftime);
    }

    inline std::string get_file_directory(std::string filename)
    {
        namespace fs = std::experimental::filesystem;

        fs::path file_path{filename};
        std::string root_dir;
        if (file_path.has_parent_path())
        {
            root_dir = file_path.parent_path().string();
        }

        return root_dir;
    }
} // namespace zeus
