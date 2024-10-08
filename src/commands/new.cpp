//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

//
// This file implements the help command.

#include <fmt/color.h>
#include <fmt/core.h>

#include <commands/help.hpp>
#include <commands/new.hpp>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string_view>

namespace fs = std::filesystem;

namespace new_cmd {

namespace {
void error_missing_path() {
  help::fatal_error(fmt::format(
      R"(the following required arguments were not provided:
{}

{} {} {}

For more information, try '{}'
)",
      fmt::format(fg(help::blue) | fmt::emphasis::bold, "  <path>"),
      fmt::format(fg(help::green) | fmt::emphasis::bold, "Usage:"),
      fmt::format(fg(help::blue) | fmt::emphasis::bold, "cask new"),
      fmt::format(fg(help::blue), "<path>"),
      fmt::format(fg(help::blue) | fmt::emphasis::bold, "--help")));
}
}  // namespace

void run(std::span<const std::string_view> args) {
  if (args.empty()) {
    error_missing_path();
    exit(EXIT_FAILURE);
  }

  const auto project_name = args[0];

  if (fs::is_directory(project_name)) {
    fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "error:");
    std::cout << " destination " << fs::absolute(project_name)
              << " already exists\n\n";
    std::cout << "Use `cask init` to initialize the directory" << std::endl;

    return;
  }

  fs::path path{project_name};

  fs::create_directories(path);
  fs::create_directories(path / "src");

  std::ofstream main_file(path / "src" / "main.cpp");

  main_file << "#include <iostream>\n\n";
  main_file << "int main() {\n";
  main_file << "    std::cout << \"Hello World!\" << std::endl;";
  main_file << "    return 0;\n";
  main_file << "}\n";

  main_file.close();

  std::ofstream gitignore_file(path / ".gitignore");
  gitignore_file.close();

  std::ofstream cask_file(path / "Cask.toml");

  cask_file << "[package]\n";
  cask_file << "name = \"" << project_name << "\"\n";
  cask_file << "version = \"0.1.0\"\n";
  cask_file << "standard = \"20\"\n\n";
  cask_file << "[dependencies]\n";

  cask_file.close();

  fmt::print(fg(fmt::color::light_green) | fmt::emphasis::bold,
             "     Created ");
  std::cout << "binary (application) `" << project_name << "` package"
            << std::endl;
}

}  // namespace new_cmd
