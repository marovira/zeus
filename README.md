# Zeus

> A C++ utilities library

[![Generic badge](https://img.shields.io/badge/License-BSD3-blue)](LICENSE)
[![Generic badge](https://img.shields.io/badge/Language-C++17-red.svg)](https://en.wikipedia.org/wiki/C%2B%2B17)
[![Build status](https://ci.appveyor.com/api/projects/status/jnwfj58q927n864i?svg=true)](https://ci.appveyor.com/project/marovira/zeus)
[![Build Status](https://travis-ci.org/marovira/zeus.svg?branch=master)](https://travis-ci.org/marovira/zeus)

## What is Zeus?

Zeus is a C++ utility library that was born from the core modules shared across
my three other projects: Atlas, Apollo, and Hermes. Since the modules are
virtually identical and updates are generally shared across projects, it made
updating them tedious. By separating them into their own project, these
utilities can now be shared across multiple projects and simplify updating. In
order to simplify and streamline dependencies, Zeus is shipped as a header-only
library.

## Dependencies

The following are **core** requirements of Zeus:

* CMake 3.12+

Zeus supports the following platforms and compilers:

| **Platform (Compiler) | **Version** |
|------------------------|-------------|
| Windows (MSVC) | 19.25 |
| Linux (GCC) | 9.2 |
| Linux (LLVM Clang) | 9.0 |

Please note that macOS is **not** supported.

In addition, Zeus depends on the following libraries:

* [FMT](https://github.com/fmtlib/fmt),
* [magic_enum](https://github.com/Neargye/magic_enum).

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

Atlas is published under the BSD-3 license and can be viewed
[here](https://github.com/marovira/zeus/blob/master/LICENSE).
