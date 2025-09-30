#pragma once

namespace zeus
{
    enum class Compiler
    {
        msvc = 0,
        gcc,
        clang
    };

#if defined(_MSC_VER)
#    define ZEUS_COMPILER_MSVC
    static constexpr auto current_compiler{Compiler::msvc};
#elif defined(__clang__)
#    define ZEUS_COMPILER_CLANG
    static constexpr auto current_compiler{Compiler::clang};
#elif defined(__GNUC__)
#    define ZEUS_COMPILER_GCC
    static constexpr auto current_compiler{Compiler::gcc};
#endif
} // namespace zeus
