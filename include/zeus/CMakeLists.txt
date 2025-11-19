set(INCLUDE_ROOT ${CMAKE_CURRENT_LIST_DIR})

set(ZEUS_VERSION_HEADER
    ${INCLUDE_ROOT}/zeus.hpp
    )
configure_file(${INCLUDE_ROOT}/zeus.hpp.in ${ZEUS_VERSION_HEADER})

set(ZEUS_INCLUDE_LIST
    ${ZEUS_VERSION_HEADER}
    ${INCLUDE_ROOT}/assert.hpp
    ${INCLUDE_ROOT}/float.hpp
    ${INCLUDE_ROOT}/platform.hpp
    ${INCLUDE_ROOT}/timer.hpp
    ${INCLUDE_ROOT}/filesystem.hpp
    ${INCLUDE_ROOT}/compiler.hpp
    ${INCLUDE_ROOT}/algorithm.hpp
    ${INCLUDE_ROOT}/crtp.hpp
    ${INCLUDE_ROOT}/type_traits.hpp
    ${INCLUDE_ROOT}/named_type.hpp
    ${INCLUDE_ROOT}/enum_bitfield.hpp
    ${INCLUDE_ROOT}/concepts.hpp
    ${INCLUDE_ROOT}/random.hpp
    ${INCLUDE_ROOT}/string.hpp
    ${INCLUDE_ROOT}/range.hpp
    ${INCLUDE_ROOT}/container_traits.hpp
    ${INCLUDE_ROOT}/linspace.hpp
    )

source_group("include" FILES)
source_group("include\\zeus" FILES ${ZEUS_INCLUDE_LIST})

add_library(zeus INTERFACE)
target_include_directories(zeus INTERFACE
    $<BUILD_INTERFACE:${ZEUS_SOURCE_ROOT}>
    $<INSTALL_INTERFACE:include>)
target_link_libraries(zeus INTERFACE fmt::fmt magic_enum::magic_enum)
if (MSVC)
    target_compile_options(zeus INTERFACE /Zc:__cplusplus)
endif()
if (NOT MSVC AND NOT APPLE)
    target_link_libraries(zeus INTERFACE stdc++fs)
endif()
target_compile_features(zeus INTERFACE cxx_std_20)
add_library(zeus::zeus ALIAS zeus)

# Add a dummy target for MSVC so the files are visible.
if (MSVC)
    add_custom_target(_zeus SOURCES ${ZEUS_INCLUDE_LIST})
    set_target_properties(_zeus PROPERTIES FOLDER "zeus")
endif()

set(ZEUS_INSTALL_FILES ${ZEUS_INCLUDE_LIST} PARENT_SCOPE)
