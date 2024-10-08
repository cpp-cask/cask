//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

//
// This file implements the help command.

#include <fmt/core.h>

#include <commands/help.hpp>
#include <iostream>

namespace help {

void run() {
  fmt::print(
      R"(C++'s package manager

{} {}

{}
    {}  Compile the current package
    {}    Create a new cask package
    {}    Run a binary or example of the local package
)",
      fmt::format(fg(green) | fmt::emphasis::bold, "Usage:"),
      fmt::format(fg(blue) | fmt::emphasis::bold, "cask [COMMAND]"),
      fmt::format(fg(green) | fmt::emphasis::bold, "Commands:"),
      fmt::format(fg(blue) | fmt::emphasis::bold, "build"),
      fmt::format(fg(blue) | fmt::emphasis::bold, "new"),
      fmt::format(fg(blue) | fmt::emphasis::bold, "run"));
}

void list() {
  fmt::print(R"(Installed Commands:
  build                Compile a local package and all of its dependencies
  help                 Displays help for a cask subcommand
  new                  Create a new cask package at <path>
  run                  Run a binary or example of the local package)");
}

void fatal_error(const std::string_view msg) {
  fmt::print(R"({} {})", fmt::format(fg(red) | fmt::emphasis::bold, "error:"),
             msg);
}

}  // namespace help
