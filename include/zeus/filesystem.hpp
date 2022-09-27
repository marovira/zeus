#pragma once

#include "platform.hpp"

#include <chrono>
#include <fmt/printf.h>
#include <string>

// It seems that in GCC and Clang the implementation of filesystem is not complete. This
// mainly affects get_file_last_write, so we're going to need to branch of a different
// implementation for that function
#if defined(ZEUS_PLATFORM_WINDOWS)
#    include <filesystem>
#else
#    include <experimental/filesystem>
#endif

namespace zeus
{
    inline std::time_t get_file_last_write(std::string filename)
    {
#if defined(ZEUS_PLATFORM_WINDOWS)
        namespace fs = std::filesystem;
#else
        namespace fs = std::experimental::filesystem;
#endif

        fs::path file_path{filename};
        [[maybe_unused]] std::error_code code;
        auto ftime = fs::last_write_time(file_path, code);
        if (code && current_build == BuildType::debug)
        {
            fmt::print(stderr, "warning: ({}): {}\n", code.value(), code.message());
        }

#if defined(ZEUS_PLATFORM_WINDOWS)
        auto system_time = std::chrono::clock_cast<std::chrono::system_clock>(ftime);
        return std::chrono::system_clock::to_time_t(system_time);
#else
        return decltype(ftime)::clock::to_time_t(ftime);
#endif
    }

    inline std::string get_file_directory(std::string filename)
    {
        namespace fs = std::filesystem;

        fs::path file_path{filename};
        std::string root_dir;
        if (file_path.has_parent_path())
        {
            root_dir = file_path.parent_path().string();
        }

        return root_dir;
    }
} // namespace zeus
