#================================
# Project setup.
#================================
cmake_minimum_required(VERSION 3.24)
project(zeus VERSION 2.0.0 LANGUAGES CXX C)

if (APPLE)
    message(ERROR "Zeus does not support Apple platforms.")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Define version variables.
set(ZEUS_VERSION_MAJOR "2")
set(ZEUS_VERSION_MINOR "0")
set(ZEUS_VERSION_PATCH "0")
set(ZEUS_VERSION_EXTRA "")
set(ZEUS_VERSION "${ZEUS_VERSION_MAJOR}.${ZEUS_VERSION_MINOR}")
set(ZEUS_VERSION_FULL
    "${ZEUS_VERSION}.${ZEUS_VERSION_PATCH}${ZEUS_VERSION_EXTRA}")

#================================
# Option variables.
#================================
option(ZEUS_BUILD_TESTS "Build Zeus unit tests" ON)
option(ZEUS_INSTALL_TARGET "Create install target" OFF)

#================================
# Directory variables.
#================================
set(ZEUS_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(ZEUS_SOURCE_ROOT ${ZEUS_SOURCE_DIR}/include)
set(ZEUS_TEST_ROOT ${ZEUS_SOURCE_DIR}/test)

#================================
# Add subdirectories.
#================================
add_subdirectory(${ZEUS_SOURCE_ROOT}/zeus)
if (ZEUS_BUILD_TESTS)
    add_subdirectory(${ZEUS_TEST_ROOT})
endif()

#================================
# Source groups.
#================================
source_group("include" FILES)
source_group("include\\zeus" FILES ${ZEUS_INCLUDE_GROUP})

#================================
# Find Packages.
#================================
include(FetchContent)

# FMT tag 8.0.1
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG d141cdbeb0fb422a3fb7173b285fd38e0d1772dc
    )

# magic_enum tag v0.7.3
FetchContent_Declare(
    magic_enum
    GIT_REPOSITORY https://github.com/Neargye/magic_enum
    GIT_TAG 3d1f6a5a2a3fbcba077e00ad0ccc2dd9fefc2ca7
    )

find_package(fmt QUIET)
find_package(magic_enum QUIET)

if (NOT fmt_FOUND AND NOT fmt_POPULATED)
    FetchContent_Populate(fmt)
    add_subdirectory(${fmt_SOURCE_DIR} ${fmt_BINARY_DIR})
endif()

if (NOT magic_enum_FOUND AND NOT magic_enum_POPULATED)
    FetchContent_Populate(magic_enum)
    add_subdirectory(${magic_enum_SOURCE_DIR} ${magic_enum_BINARY_DIR})
endif()

#================================
# Main library.
#================================
add_library(zeus INTERFACE)
target_include_directories(zeus INTERFACE 
    $<BUILD_INTERFACE:${ZEUS_SOURCE_ROOT}>
    $<INSTALL_INTERFACE:include>)
target_link_libraries(zeus INTERFACE fmt::fmt magic_enum::magic_enum)
if (NOT MSVC)
    target_link_libraries(zeus INTERFACE stdc++fs)
endif()
target_compile_features(zeus INTERFACE cxx_std_20)
add_library(zeus::zeus ALIAS zeus)

# Add a dummy target for MSVC so the files are visible.
if (MSVC)
    add_custom_target(_zeus SOURCES ${ZEUS_INCLUDE_GROUP})
    set_target_properties(_zeus PROPERTIES FOLDER "zeus")
endif()

#================================
# Install targets.
#================================
if (ZEUS_INSTALL_TARGET)
    if (MSVC)
        set(INCLUDE_INSTALL_PATH "include")
    else()
        set(INCLUDE_INSTALL_PATH "include/libzeus")
    endif()

    install(TARGETS zeus
        EXPORT zeus
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION lib
        INCLUDES DESTINATION ${INCLUDE_INSTALL_PATH}
        )

    include(CMakePackageConfigHelpers)
    include(GNUInstallDirs)
    write_basic_package_version_file(
        "${PROJECT_BINARY_DIR}/zeusConfigVersion.cmake"
        VERSION ${PACKAGE_VERSION}
        COMPATIBILITY AnyNewerVersion
        )

    install(EXPORT zeus 
        FILE zeusTargets.cmake
        NAMESPACE zeus::
        DESTINATION lib/cmake/zeus
        )

    install(FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/zeus-config.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/zeusConfigVersion.cmake"
        DESTINATION lib/cmake/zeus
        )

    if (MSVC)
        set(INCLUDE_INSTALL_DEST "${CMAKE_INSTALL_INCLUDEDIR}/zeus")
    else()
        set(INCLUDE_INSTALL_DEST "${CMAKE_INSTALL_INCLUDEDIR}/libzeus/zeus")
    endif()
    install(FILES
        ${ZEUS_INCLUDE_GROUP}
        DESTINATION ${INCLUDE_INSTALL_DEST}
        )
endif()

#================================
# Build the tests.
#================================
if (ZEUS_BUILD_TESTS)
    # Catch tag v2.13.6
    FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG 5c88067bd339465513af4aec606bd2292f1b594a
        )

    find_package(Catch2 QUIET)
    if (NOT Catch2_FOUND AND NOT catch2_POPULATED)
        FetchContent_Populate(catch2)
        add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
        set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${catch2_SOURCE_DIR}/contrib)
    endif()

    source_group("source" FILES ${ZEUS_TEST_GROUP})
    add_executable(zeus_test ${ZEUS_TEST_LIST})
    target_link_libraries(zeus_test
        zeus
        Catch2::Catch2)
    set_target_properties(zeus_test PROPERTIES FOLDER "zeus")

    include(CTest)
    include(Catch)
    catch_discover_tests(zeus_test)
endif()
