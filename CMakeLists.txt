#================================
# Project setup.
#================================
cmake_minimum_required(VERSION 3.27)
project(zeus VERSION 1.3.0 LANGUAGES CXX C)

if (APPLE)
    message(ERROR "Zeus does not support Apple platforms.")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

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

find_package(fmt 10.2.0 QUIET)
find_package(magic_enum 0.9.5 QUIET)

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

    if (MSVC)
        set(INCLUDE_INSTALL_DEST "${CMAKE_INSTALL_INCLUDEDIR}/zeus")
    else()
        set(INCLUDE_INSTALL_DEST "${CMAKE_INSTALL_INCLUDEDIR}/libzeus/zeus")
    endif()
    install(FILES
        ${ZEUS_INSTALL_FILES}
        DESTINATION ${INCLUDE_INSTALL_DEST}
        )
endif()

#================================
# Build the tests.
#================================
if (ZEUS_BUILD_TESTS)
    find_package(Catch2 3.5.1 QUIET)

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
