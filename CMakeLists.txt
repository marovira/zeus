#================================
# Project setup.
#================================
cmake_minimum_required(VERSION 3.30)
project(zeus VERSION 1.5.0 LANGUAGES CXX C)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Don't allow builds for Apple.
if (APPLE)
    message(ERROR "Zeus does not support Apple platforms")
endif()

# Generate compilation database on all Unix systems
if (NOT MSVC)
    set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

#================================
# Option variables.
#================================
option(ZEUS_BUILD_TESTS "Build Zeus unit tests" OFF)
option(ZEUS_INSTALL_TARGET "Create install target" OFF)

#================================
# Directory variables.
#================================
set(ZEUS_SOURCE_DIR ${PROJECT_SOURCE_DIR})
set(ZEUS_SOURCE_ROOT ${ZEUS_SOURCE_DIR}/include)
set(ZEUS_TEST_ROOT ${ZEUS_SOURCE_DIR}/test)
set(ZEUS_CMAKE_ROOT ${ZEUS_SOURCE_DIR}/cmake)

#================================
# Find Packages.
#================================
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ZEUS_CMAKE_ROOT})

include(FetchContent)
include(FetchLibrary)

#================================
# SDK Versions.
#================================
set(ZEUS_FMT_VERSION 11.0.0)
set(ZEUS_MAGIC_ENUM_VERSION 0.9.6)
set(ZEUS_CATCH_VERSION 3.7.1)

find_package(fmt ${ZEUS_FMT_VERSION} QUIET)
find_package(magic_enum ${ZEUS_MAGIC_ENUM_VERSION} QUIET)

if (NOT fmt_FOUND)
    fetch_library(
        NAME fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 67c0c0c09cf74d407d71a29c194761981614df3e
        )
endif()

if (NOT magic_enum_FOUND)
    fetch_library(
        NAME magic_enum
        GIT_REPOSITORY https://github.com/Neargye/magic_enum
        GIT_TAG e55b9b54d5cf61f8e117cafb17846d7d742dd3b4
        )
endif()

#================================
# Add subdirectories.
#================================
add_subdirectory(${ZEUS_SOURCE_ROOT}/zeus)

#================================
# Install targets.
#================================
if (ZEUS_INSTALL_TARGET)
    install(TARGETS zeus
        EXPORT zeus
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION lib
        INCLUDES DESTINATION include
        )

    include(CMakePackageConfigHelpers)
    include(GNUInstallDirs)
    write_basic_package_version_file(
        "${PROJECT_BINARY_DIR}/zeusConfigVersion.cmake"
        VERSION ${PACKAGE_VERSION}
        COMPATIBILITY SameMajorVersion
        ARCH_INDEPENDENT
        )

    install(EXPORT zeus
        FILE zeusTargets.cmake
        NAMESPACE zeus::
        DESTINATION lib/cmake/zeus
        )

    install(FILES
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/zeusConfig.cmake"
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/FetchLibrary.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/zeusConfigVersion.cmake"
        DESTINATION lib/cmake/zeus
        )

    install(FILES
        ${ZEUS_INSTALL_FILES}
        DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}/zeus"
        )
endif()

#================================
# Build the tests.
#================================
if (ZEUS_BUILD_TESTS)
    find_package(Catch2 ${ZEUS_CATCH_VERSION} QUIET)

    if (NOT Catch2_FOUND)
        fetch_library(
            NAME Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG f981c9cbcac07a2690e5a86767eba490b5465463
            )
        list(APPEND CMAKE_MODULE_PATH ${Catch2_SOURCE_DIR}/extras)
    endif()

    include(CTest)
    include(Catch)

    add_subdirectory(${ZEUS_TEST_ROOT})
endif()

# Make a symlink for the compile_commands.json file
if (NOT MSVC)
    file(CREATE_LINK
        "${CMAKE_BINARY_DIR}/compile_commands.json"
        "${ZEUS_SOURCE_DIR}/compile_commands.json"
        SYMBOLIC)
endif()
