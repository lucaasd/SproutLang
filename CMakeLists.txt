cmake_minimum_required(VERSION 3.20)

project(SproutLang)

find_package(GTest CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)
file(GLOB_RECURSE SPROUT_COMPILER src/compiler/*.cpp)
file(GLOB_RECURSE SPROUT_COMPILER_TESTS test/compiler/*.cpp)

add_library(SproutCompiler ${SPROUT_COMPILER})

add_executable(SproutCompilerTests ${SPROUT_COMPILER_TESTS})
target_link_libraries(SproutCompilerTests PRIVATE GTest::gtest GTest::gtest_main SproutCompiler)
target_include_directories(SproutCompilerTests PRIVATE src/)
