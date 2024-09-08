<a id="top"></a>
![Zeus logo](data/logo/logo-transparent.png)

[![Build](https://github.com/marovira/zeus/actions/workflows/build.yml/badge.svg)](https://github.com/marovira/zeus/actions/workflows/build.yml)
[![CodeFactor](https://www.codefactor.io/repository/github/marovira/zeus/badge/master)](https://www.codefactor.io/repository/github/marovira/zeus/overview/master)
[![Generic badge](https://img.shields.io/badge/Language-C++20-red.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![Generic badge](https://img.shields.io/badge/License-BSD3-blue)](LICENSE)

## What is Zeus?

Named after the Greek god of the sky and thunder and king of Olympus, Zeus is a C++
utility library that serves as the bedrock for all of my projects. It is built as a
header-only library for ease of use that contains several utilities aimed at making coding
in C++ easier. Some notable features of Zeus are:

* A type-safe wrapper for performing bitwise operations on `enum class` types,
* A customizable, cross-platform `assert` macro,
* Several concepts for template programming,
* Python-like functions for string operations,
* A python-like version of `range`.

## Dependencies

The following are **core** requirements of Zeus:

* CMake 3.27+

Zeus supports the following platforms and compilers:

| Platform (Compiler) | Version |
|---------------------|---------|
| Windows (MSVC) | 19.41 |
| Linux (GCC) | 14 |
| Linux (LLVM Clang) | 18.0 |
| Apple (Apple Clang) | 15.0 |

In addition, Zeus depends on the following libraries:

| Library | Version |
|---------|---------|
| [FMT](https://github.com/fmtlib/fmt) | 11.0.0 |
| [magic_enum](https://github.com/Neargye/magic_enum) | 0.9.6 |

## Contributing

There are three ways in which you can contribute to Zeus:

* If you find a bug, please open an issue. Similarly, if you have a question
  about how to use it, or if something is unclear, please post an issue so it
  can be addressed.
* If you have a fix for a bug, or a code enhancement, please open a pull
  request. Before you submit it though, make sure to abide by the rules written
  below.
* If you have a feature proposal, you can either open an issue or create a pull
  request. If you are submitting a pull request, it must abide by the rules
  written below. Note that any new features need to be approved by me.

If you are submitting a pull request, the guidelines are the following:

1. Ensure that your code follows the standards and formatting of the framework.
   The coding standards can be seen throughout the code, and the formatting is
   handled through the `.clang-format` file located at the root of the
   directory. Any changes that do not follow the style and format will be
   rejected.
2. Ensure that *all* unit tests are working prior to submitting the pull
   request. If you are adding a new feature that has been approved, it is your
   responsibility to provide the corresponding unit tests (if applicable).

## License

Zeus is published under the BSD-3 license and can be viewed
[here](https://github.com/marovira/zeus/blob/master/LICENSE).
