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
#include <unordered_map>

namespace fs = std::filesystem;

namespace add {

namespace {
void error_missing_argument() {
  help::fatal_error(fmt::format(
      R"(the following required arguments were not provided:
{}

{} {} {}

For more information, try '{}'
)",
      fmt::format(fg(help::blue) | fmt::emphasis::bold, "  <DEP_ID>"),
      fmt::format(fg(help::green) | fmt::emphasis::bold, "Usage:"),
      fmt::format(fg(help::blue) | fmt::emphasis::bold, "cask add"),
      fmt::format(fg(help::blue), "<DEP>[@VERSION]"),
      fmt::format(fg(help::blue) | fmt::emphasis::bold, "--help")));
  exit(EXIT_FAILURE);
}

void error_unknown_command(const std::string_view library) {
  help::fatal_error(fmt::format(
      R"(the library `{}` could not be found in registry index.
)",
      library));
  exit(EXIT_FAILURE);
}

struct Library {
  std::string_view last_version;
};

static const std::unordered_map<std::string_view, Library> libraries{
    {"fmt", {"11.0.2"}},
};
}  // namespace

void run(const std::span<char *> args) {
  if (args.empty()) {
    error_missing_argument();
  }

  const auto library = args[0];

  if (auto it{libraries.find(library)}; it != libraries.end()) {
    const fs::path path{fs::current_path()};

    if (!fs::exists(path / "Cask.toml")) {
      fmt::print(fg(fmt::color::red) | fmt::emphasis::bold, "error:");
      std::cout << "could not find `Cask.toml` in " << fs::absolute(path)
                << " or any parent directory" << std::endl;
      return;
    }

    std::ofstream cask_file(path / "Cask.toml", std::ios::app);

    cask_file << fmt::format("{} = \"{}\"", library, it->second.last_version);

    cask_file.close();

    fmt::print(
        R"(      {} {} v{}
)",
        fmt::format(fg(help::blue) | fmt::emphasis::bold, "Adding"), library,
        it->second.last_version);

  } else {
    error_unknown_command(library);
  }
}

}  // namespace add
