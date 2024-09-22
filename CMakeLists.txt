cmake_minimum_required(VERSION 3.16)

# set the project name and version
project(Cask VERSION 0.1)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# add the executable
add_executable(cask src/main.cpp)

# add dependencies
include(cmake/CPM.cmake)

CPMAddPackage("gh:fmtlib/fmt#11.0.2")

# link dependencies
target_link_libraries(cask fmt::fmt)

# Install
install(TARGETS cask)

# Test
enable_testing()
add_test(NAME cask COMMAND cask help)