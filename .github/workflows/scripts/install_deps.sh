#!/bin/bash

if [ ! -d ~/deps ]; then
    python3 .github/workflows/scripts/generate_versions.py

    # Read the necessary versions.
    fmt_ver=$(<~/zeus_fmt_version.txt)
    catch_ver="v$(<~/zeus_catch_version.txt)"
    me_ver="v$(<~/zeus_magic_enum_version.txt)"

    mkdir ~/deps
    git clone https://github.com/Neargye/magic_enum --branch $me_ver --depth 1
    cmake -S magic_enum -B magic_enum/build --parallel -DCMAKE_CXX_STANDARD=20 -DMAGIC_ENUM_OPT_BUILD_EXAMPLES=OFF -DMAGIC_ENUM_OPT_INSTALL=ON -DMAGIC_ENUM_OPT_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=~/deps/magic_enum
    cd ./magic_enum/build
    make
    make install
    cd ../..

    git clone https://github.com/fmtlib/fmt.git --branch $fmt_ver --depth 1
    cmake -S fmt -B fmt/build --parallel -DCMAKE_CXX_STANDARD=20 -DFMT_INSTALL=ON -DFMT_TEST=OFF -DCMAKE_INSTALL_PREFIX=~/deps/fmt
    cd ./fmt/build
    make
    make install
    cd ../..
    git clone https://github.com/catchorg/Catch2.git --branch $catch_ver --depth 1
    cmake -S Catch2 -B Catch2/build --parallel -DCMAKE_CXX_STANDARD=20 -DCATCH_INSTALL_DOCS=OFF -DCMAKE_INSTALL_PREFIX=~/deps/Catch2
    cd ./Catch2/build
    make
    make install
fi
