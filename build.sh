#!/usr/bin/env bash

set -euo pipefail

export Compiler=clang
export Version=13
export Arch=x86_64
export BuildType=Debug
export Runtime=MT

conan install . -if build --build outdated \
    -pr .conan/profiles/profile.jinja -pr:b .conan/profiles/profile.jinja \
    -c tools.cmake.cmaketoolchain:generator=Ninja \
    -e CONAN_CMAKE_GENERATOR=Ninja

conan build . -bf build
