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
set(ZEUS_CMAKE_ROOT ${ZEUS_SOURCE_DIR}/cmake)

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
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ZEUS_CMAKE_ROOT})

include(FetchContent)
include(FetchLibrary)

find_package(fmt 9.1.0 QUIET)
find_package(magic_enum 0.8.2 QUIET)

if (NOT fmt_FOUND)
    fetch_library(
        NAME fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG a33701196adfad74917046096bf5a2aa0ab0bb50
        )
endif()

if (NOT magic_enum_FOUND)
    fetch_library(
        NAME magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum
        GIT_TAG e1a68e9dd3d2e9180b04c8aeacd4975db745e6b8
        )
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
    find_package(Catch2 3.3.2 QUIET)

    if (NOT Catch2_FOUND)
        fetch_library(
            NAME Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG 97c48e0c343d26d50764fafdc90b1e630fbd10ce
            )
        list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
    endif()

    source_group("source" FILES ${ZEUS_TEST_GROUP})
    add_executable(zeus_test ${ZEUS_TEST_LIST})
    target_link_libraries(zeus_test PRIVATE
        zeus
        Catch2::Catch2WithMain)
    set_target_properties(zeus_test PROPERTIES FOLDER "zeus")

    include(CTest)
    include(Catch)
    catch_discover_tests(zeus_test)
endif()
