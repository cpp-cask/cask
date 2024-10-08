cmake_minimum_required(VERSION 3.29)

# set the project name and version
project(
    Cask 
    VERSION 0.1
    LANGUAGES CXX C)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Recursively gather all source files from src folder and its subdirectories
file(GLOB_RECURSE SRC_FILES "src/*.cpp")
list(FILTER SRC_FILES EXCLUDE REGEX ".test.")
list(FILTER SRC_FILES EXCLUDE REGEX "main.cpp")

# add the executable
add_executable(cask ${SRC_FILES} src/main.cpp)

# Add the src folder as an include directory so headers can be found
target_include_directories(cask PRIVATE ${CMAKE_SOURCE_DIR}/src)

# add dependencies
include(cmake/CPM.cmake)

CPMAddPackage("gh:fmtlib/fmt#11.0.2")
CPMAddPackage("gh:catchorg/Catch2@3.7.1")
CPMAddPackage("gh:marzer/tomlplusplus@3.4.0")

# link dependencies
target_link_libraries(cask fmt::fmt tomlplusplus::tomlplusplus)

# Install
install(TARGETS cask)

# Test
# Recursively gather all test files from src folder and its subdirectories
file(GLOB_RECURSE TEST_FILES_INPLACE "src/*.test.cpp")
file(GLOB_RECURSE TEST_FILES_FOLDER "tests/*.cpp")

# add the executable
add_executable(cask-test ${TEST_FILES_INPLACE} ${TEST_FILES_FOLDER} ${SRC_FILES})

target_include_directories(cask-test PRIVATE ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(cask-test fmt::fmt Catch2::Catch2WithMain tomlplusplus::tomlplusplus)

enable_testing()
add_test(NAME cask COMMAND cask help)
add_test(NAME cask-test COMMAND cask-test)