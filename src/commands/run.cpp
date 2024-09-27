//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

//
// This file implements the help command.

#include <fmt/color.h>

#include <cassert>
#include <commands/run.hpp>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string_view>

namespace fs = std::filesystem;

namespace run {

void run(std::string_view project_name) {
  fs::path path{fs::current_path()};

  if (!fs::exists(path / "Cask.toml")) {
    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "error:");
    std::cout << "could not find `Cask.toml` in " << fs::absolute(project_name)
              << " or any parent directory" << std::endl;
    return;
  }

  if (!fs::is_directory(path / "target")) {
    fs::create_directories(path / "target");
  }

  if (!fs::is_directory(path / "target" / "debug")) {
    fs::create_directories(path / "target" / "debug");
  }

  if (!fs::is_directory(path / "target" / "debug" / "build")) {
    fs::create_directories(path / "target" / "debug" / "build");
  }

  std::ofstream cmake_file(path / "target" / "debug" / "CMakeLists.txt");

  cmake_file << "cmake_minimum_required(VERSION 3.16)\n\n";
  cmake_file << "# set the project name and version\n";
  cmake_file << "project(paco VERSION 0.1)\n\n";

  cmake_file << "# specify the C++ standard\n";
  cmake_file << "set(CMAKE_CXX_STANDARD 17)\n";
  cmake_file << "set(CMAKE_CXX_STANDARD_REQUIRED True)\n\n";

  cmake_file << "# Recursively gather all source files from src folder and its "
                "subdirectories\n";
  cmake_file << "file(GLOB_RECURSE SRC_FILES \"../../src/*.cpp\")\n\n";

  cmake_file << "#add the executable\n";
  cmake_file << "add_executable(paco ${SRC_FILES})\n\n";

  cmake_file << "#Add the src folder as an include directory so headers can be "
                "found\n";
  cmake_file
      << "target_include_directories(paco PRIVATE ${CMAKE_SOURCE_DIR}/src)\n\n";

  cmake_file << "#add dependencies\n";

  cmake_file.close();

  assert(std::system("cmake -Starget/debug -Btarget/debug/build") == 0);
  assert(std::system("cmake --build target/debug/build") == 0);
}

}  // namespace run
