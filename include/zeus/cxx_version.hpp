#pragma once

namespace zeus
{
    enum class CXXVersion
    {
        std_17,
        std_20,
        std_23,
    };

    // NOLINTBEGIN(cppcoreguidelines-macro-usage)
#define ZEUS_CXX_VERSION __cplusplus
#define ZEUS_CXX_17      201'703L
#define ZEUS_CXX_20      202'002L
#define ZEUS_CXX_23      202'302L
    // NOLINTEND(cppcoreguidelines-macro-usage)

#if ZEUS_CXX_VERSION < ZEUS_CXX_20
#    error "Zeus requires a minimum compiler support of C++20"
#elif ZEUS_CXX_VERSION == ZEUS_CXX_20
    static constexpr CXXVersion current_cxx_version{CXXVersion::std_20};
#elif ZEUS_CXX_VERSION == ZEUS_CXX_23
    static constexpr CXXVersion current_cxx_version{CXXVersion::std_23};
#else
#    error \
        "New version of C++ found. Please update cxx_version.hpp with the new C++ version"
#endif
} // namespace zeus
