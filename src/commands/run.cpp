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
#include <functional>
#include <iostream>
#include <map>
#include <string_view>
#include <toml++/toml.hpp>

namespace fs = std::filesystem;

namespace run {

struct Dependency {
  std::string library;
  std::function<std::string(const std::string&)> generator;
};

static const std::map<std::string, Dependency> dependency_map{
    {"fmt",
     {"fmt::fmt",
      [](const std::string& version) {
        std::string result{"CPMAddPackage(\"gh:fmtlib/fmt#"};
        result += version;
        result += "\")";
        return result;
      }}},
    {"tomlplusplus",
     {"tomlplusplus::tomlplusplus", [](const std::string& version) {
        std::string result{"CPMAddPackage(\"gh:marzer/tomlplusplus@"};
        result += version;
        result += "\")";
        return result;
      }}}};

void run() {
  const fs::path path{fs::current_path()};

  if (!fs::exists(path / "Cask.toml")) {
    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "error:");
    std::cout << "could not find `Cask.toml` in " << fs::absolute(path)
              << " or any parent directory" << std::endl;
    return;
  }

  std::string project_name{};
  std::string cxx_version{};
  std::map<std::string, std::string> dependencies_map{};

  try {
    auto config = toml::parse_file((path / "Cask.toml").string().c_str());

    if (auto package = config["package"].as_table()) {
      // Access the 'name' key and ensure it's a string
      if (auto name = package->get("name")->value<std::string_view>()) {
        project_name = *name;
        std::cout << "Project name: " << project_name << std::endl;
      } else {
        std::cerr << "'name' is not a valid string" << std::endl;
      }

      if (auto standard = package->get("standard")->value<std::string_view>()) {
        cxx_version = *standard;
        std::cout << "standard: " << cxx_version << std::endl;
      } else {
        std::cerr << "'standard' is not a valid string" << std::endl;
      }
    } else {
      std::cerr << "[package] table not found" << std::endl;
    }

    // Access the 'dependencies' table
    if (auto dependencies = config["dependencies"].as_table()) {
      // Iterate over all key-value pairs in the dependencies table
      for (const auto& [key, value] : *dependencies) {
        if (const auto version = value.value<std::string_view>()) {
          dependencies_map.emplace(key, *version);
        }
      }

      // Output all the dependencies and their versions
      for (const auto& [name, version] : dependencies_map) {
        std::cout << "Dependency: " << name << ", Version: " << version << '\n';
      }
    } else {
      std::cerr << "[dependencies] table not found." << std::endl;
    }
  } catch (const toml::parse_error& err) {
    // std::cerr << "Parsing failed: " << err << std::endl;
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
  cmake_file << "project(" << project_name << " VERSION 0.1)\n\n";

  cmake_file << "# specify the C++ standard\n";
  cmake_file << "set(CMAKE_CXX_STANDARD " << cxx_version << ")\n";
  cmake_file << "set(CMAKE_CXX_STANDARD_REQUIRED True)\n\n";

  cmake_file << "# Recursively gather all source files from src folder and its "
                "subdirectories\n";
  cmake_file << "file(GLOB_RECURSE SRC_FILES \"../../src/*.cpp\")\n\n";

  cmake_file << "#add the executable\n";
  cmake_file << "add_executable(" << project_name << " ${SRC_FILES})\n\n";

  cmake_file << "#Add the src folder as an include directory so headers can be "
                "found\n";
  cmake_file << "target_include_directories(" << project_name
             << " PRIVATE ${CMAKE_SOURCE_DIR}/src)\n\n";

  cmake_file << "#add dependencies\n";

  cmake_file << "file(\n";
  cmake_file << "  DOWNLOAD\n";
  cmake_file << "  "
                "https://github.com/cpm-cmake/CPM.cmake/releases/download/"
                "v0.40.2/CPM.cmake\n";
  cmake_file << "  ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake\n";
  cmake_file
      << "  EXPECTED_HASH "
         "SHA256="
         "c8cdc32c03816538ce22781ed72964dc864b2a34a310d3b7104812a5ca2d835d\n";
  cmake_file << ")\n";
  cmake_file << "include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)\n\n";

  for (auto const& [key, val] : dependencies_map) {
    const auto it = dependency_map.find(key);
    if (it != dependency_map.end()) {
      cmake_file << it->second.generator(val) << '\n';
    }
  }

  if (!dependencies_map.empty()) {
    cmake_file << "\ntarget_link_libraries(" << project_name;
    for (auto const& [key, val] : dependencies_map) {
      const auto it = dependency_map.find(key);
      if (it != dependency_map.end()) {
        cmake_file << " " << it->second.library;
      }
    }
  }

  cmake_file << ")\n";

  cmake_file.close();

  std::string command{"cmake -S"};
  command += (path / "target" / "debug").string();
  command += " -B";
  command += (path / "target" / "debug" / "build").string();

  assert(std::system(command.c_str()) == 0);

  command = "cmake --build ";
  command += (path / "target" / "debug" / "build").string();

  assert(std::system(command.c_str()) == 0);

  command = (path / "target" / "debug" / "build" / project_name).string();

  std::system(command.c_str());
}

}  // namespace run
