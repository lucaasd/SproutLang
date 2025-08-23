cmake_minimum_required(VERSION 3.20)

project(SproutLang)

set(CMAKE_CXX_STANDARD 23)
file(GLOB_RECURSE SPROUT_COMPILER src/compiler/*.cpp)

add_library(SproutCompiler ${SPROUT_COMPILER})
