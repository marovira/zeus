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
    static constexpr Compiler current_compiler{Compiler::msvc};
#elif defined(__GNUC__)
#    define ZEUS_COMPILER_GCC
    static constexpr Compiler current_compiler{Compiler::gcc};
#elif defined(__clang__)
#    define ZEUS_COMPILER_CLANG
    static constexpr Compiler current_compiler{Compiler::clang};
#endif

} // namespace zeus
