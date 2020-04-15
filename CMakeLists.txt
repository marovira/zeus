#================================
# Project setup.
#================================
cmake_minimum_required(VERSION 3.12)
project(zeus VERSION 1.0.0 LANGUAGES CXX C)

if (APPLE)
    message(ERROR "Zeus does not support Apple platforms.")
endif()

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Define version variables.
set(ZEUS_VERSION_MAJOR "1")
set(ZEUS_VERSION_MINOR "0")
set(ZEUS_VERSION_PATCH "0")
set(ZEUS_VERSION_EXTRA "")
set(ZEUS_VERSION "${ZEUS_VERSION_MAJOR}.${ZEUS_VERSION_MINOR}")
set(ZEUS_VERSION_FULL
    "${ZEUS_VERSION}.${ZEUS_VERSION_PATCH}${ZEUS_VERSION_EXTRA}")

if (POLICY CMP0072)
    cmake_policy(SET CMP0072 NEW)
endif()

#================================
# Option variables.
#================================
option(ZEUS_BUILD_TESTS "Build Zeus unit tests" ON)

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

#================================
# Source groups.
#================================
source_group("include" FILES)
source_group("include\\zeus" FILES ${ZEUS_INCLUDE_GROUP})

#================================
# Clang targets.
#================================
find_program(CLANG_FORMAT_EXE
    NAMES "clang-format"
    DOC "Path to clang-format executable"
    )
if (NOT CLANG_FORMAT_EXE)
    message(STATUS "clang-format not found.")
else()
    message(STATUS "clang-format found: ${CLANG_FORMAT_EXE}")
    set(ZEUS_FILES
        ${ZEUS_HEADER_FILES}
        )
    add_custom_target(clang-format
        COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${ZEUS_FILES}
        )
endif()

#================================
# Find Packages.
#================================
include(FetchContent)

# Declare fetch content for all packages.
FetchContent_Declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 5899267c47c12ce0be664d913440fd9be50f20b3
    )

FetchContent_Declare(
    magic_enum
    GIT_REPOSITORY https://github.com/Neargye/magic_enum
    GIT_TAG c080a591ee9a9db5ff8ab04044a1857bbcd74e0b
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
# Compiler flags.
#================================
if (MSVC)
    set(ZEUS_COMPILER_FLAGS /W4 /WX /MP)
    set(ZEUS_DEBUG_FLAGS "$<$<CONFIG:DEBUG>:/ZI>")
    set(ZEUS_COMPILE_DEFINITIONS -DNOMINMAX)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL
        "GNU")
    set(ZEUS_COMMON_FLAGS -Wall -Wextra -pedantic -Werror)
    if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        set(ZEUS_COMPILER_FLAGS ${ZEUS_COMMON_FLAGS})
    else()
        set(ZEUS_COMPILER_FLAGS ${ZEUS_COMMON_FLAGS} -stdlib=libstdc++)
    endif()
    set(ZEUS_DEBUG_FLAGS "$<$<CONFIG:DEBUG>:-g>")
endif()

#================================
# Core module.
#================================
add_library(zeus INTERFACE)
target_include_directories(zeus INTERFACE ${ZEUS_SOURCE_ROOT})
target_link_libraries(zeus INTERFACE fmt::fmt magic_enum::magic_enum)
if (NOT MSVC)
    target_link_libraries(zeus INTERFACE stdc++fs)
endif()
target_compile_features(zeus INTERFACE cxx_std_17)
target_compile_options(zeus INTERFACE ${ZEUS_COMPILER_FLAGS})
target_compile_options(zeus INTERFACE ${ZEUS_DEBUG_FLAGS})
target_compile_definitions(zeus INTERFACE ${ZEUS_COMPILE_DEFINITIONS})
add_library(apollo::core ALIAS zeus)

# Add a dummy target for MSVC so the files are visible.
if (MSVC)
    add_custom_target(_zeus SOURCES ${ZEUS_INCLUDE_GROUP})
endif()

#================================
# Build the tests.
#================================
if (ZEUS_BUILD_TESTS)
    FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG 5d32ce26f4c18588f9eac3342aea122a38b8fed3
        )

    find_package(Catch2 QUIET)
    if (NOT Catch2_FOUND AND NOT catch2_POPULATED)
        FetchContent_Populate(catch2)
        add_subdirectory(${catch2_SOURCE_DIR} ${catch2_BINARY_DIR})
        set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${catch2_SOURCE_DIR}/contrib)
    endif()

    add_subdirectory(${ZEUS_TEST_ROOT})

    source_group("source" FILES ${ZEUS_TEST_GROUP})
    add_executable(zeus_test ${ZEUS_TEST_LIST})
    target_link_libraries(zeus_test
        zeus_core
        Catch2::Catch2)
    set_target_properties(zeus_test PROPERTIES FOLDER "tests")

    include(CTest)
    include(Catch)
    catch_discover_tests(zeus_test)
endif()
