//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

//
// This file implements the help command.

#include <fmt/color.h>

#include <commands/help.hpp>
#include <iostream>

namespace help {

constexpr fmt::color blue{fmt::color::deep_sky_blue};
constexpr fmt::color green{fmt::color::light_green};
constexpr fmt::color red{fmt::color::red};

void help() {
  std::cout << "C++'s package manager\n\n";

  fmt::print(fg(green) | fmt::emphasis::bold, "Usage: ");
  fmt::print(fg(blue) | fmt::emphasis::bold, "cask [COMMAND]\n\n");

  fmt::print(fg(green) | fmt::emphasis::bold, "Commands:\n");
  fmt::print(fg(blue) | fmt::emphasis::bold, "    new  ");
  std::cout << "Create a new cask package" << std::endl;
}

void list() {
  std::cout << "Installed Commands:\n";
  std::cout << "    help                 Displays help for a cask subcommand"
            << std::endl;
}

void unknown_command(std::string_view command) {
  fmt::print(fg(red) | fmt::emphasis::bold, "error");
  std::cout << ": no such command: `" << command << "`\n\n";
  std::cout << "        Did you mean `help`?\n\n";
  std::cout << "        View all installed commands with `cask --list`"
            << std::endl;
}

}  // namespace help
