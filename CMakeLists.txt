cmake_minimum_required(VERSION 3.20)

project(SproutLang)

find_package(GTest CONFIG REQUIRED)
find_package(fmt CONFIG REQUIRED)

set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SPROUT_COMPILER src/compiler/*.cpp)
file(GLOB_RECURSE SPROUT_COMPILER_TESTS test/compiler/*.cpp)

add_library(SproutCompiler ${SPROUT_COMPILER})

add_executable(SproutCompilerTests ${SPROUT_COMPILER_TESTS})
target_include_directories(SproutCompilerTests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_link_libraries(SproutCompilerTests PRIVATE GTest::gtest GTest::gtest_main SproutCompiler fmt::fmt)

target_compile_options(SproutCompiler PRIVATE
-Wall
-Wextra
-Wpedantic
-Wuninitialized
)
