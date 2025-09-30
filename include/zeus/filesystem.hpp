#pragma once

#include "platform.hpp"

#include <fmt/base.h>

#if !defined(ZEUS_PLATFORM_APPLE)
#    include <chrono>
#    include <cstdio>
#    include <system_error>
#endif

#include <ctime>
#include <string>

#if defined(ZEUS_PLATFORM_WINDOWS) || defined(ZEUS_PLATFORM_APPLE)
#    include <filesystem> // IWYU pragma: export
#else
#    include <experimental/filesystem> // IWYU pragma: export
#endif

namespace zeus
{
#if defined(ZEUS_PLATFORM_WINDOWS) || defined(ZEUS_PLATFORM_APPLE)
    namespace zeus_fs = std::filesystem;
#else
    namespace zeus_fs = std::experimental::filesystem;
#endif

#if !defined(ZEUS_PLATFORM_APPLE)
    inline auto get_file_last_write(std::string filename) -> std::time_t
    {
        const auto file_path = zeus_fs::path{filename};
        auto code = std::error_code{};
        auto ftime = zeus_fs::last_write_time(file_path, code);
        if (code && current_build == BuildType::debug)
        {
            fmt::print(stderr, "warning: ({}): {}\n", code.value(), code.message());
        }

#    if defined(ZEUS_PLATFORM_WINDOWS)
        auto system_time = std::chrono::clock_cast<std::chrono::system_clock>(ftime);
        return std::chrono::system_clock::to_time_t(system_time);
#    else
        return decltype(ftime)::clock::to_time_t(ftime);
#    endif
    }
#endif

    inline auto get_file_directory(std::string filename) -> std::string
    {
        const auto file_path = zeus_fs::path{filename};
        auto root_dir = std::string{};
        if (file_path.has_parent_path())
        {
            root_dir = file_path.parent_path().string();
        }

        return root_dir;
    }

    class ChdirScope
    {
    public:
        ChdirScope(zeus_fs::path const& target_path)
        {
            m_start_path = zeus_fs::current_path();
            zeus_fs::current_path(target_path);
        }

        ChdirScope(ChdirScope const&) = delete;
        ChdirScope(ChdirScope&&) = default;

        ~ChdirScope()
        {
            try
            {
                zeus_fs::current_path(m_start_path);
            }
            catch (zeus_fs::filesystem_error const&) // NOLINT(bugprone-empty-catch)
            {
                fmt::print("error: unable to switch back to {}", m_start_path.string());
            }
        }

        auto operator=(ChdirScope const&) -> ChdirScope& = delete;
        auto operator=(ChdirScope&&) -> ChdirScope& = default;

    private:
        zeus_fs::path m_start_path;
    };
} // namespace zeus
