cmake_minimum_required(VERSION 3.16)

# set the project name and version
project(Cask VERSION 0.1)

# add the executable
add_executable(cask src/main.cpp)

install(TARGETS cask)

enable_testing()
add_test(NAME cask COMMAND cask)