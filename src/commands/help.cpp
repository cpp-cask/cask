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

void run() {
  constexpr fmt::color green{fmt::color::light_green};
  constexpr fmt::color blue{fmt::color::deep_sky_blue};

  std::cout << "C++'s package manager\n\n";

  fmt::print(fg(green) | fmt::emphasis::bold, "Usage: ");
  fmt::print(fg(blue) | fmt::emphasis::bold, "cask [COMMAND]\n\n");

  fmt::print(fg(green) | fmt::emphasis::bold, "Commands:\n");
  fmt::print(fg(blue) | fmt::emphasis::bold, "    new  ");
  std::cout << "Create a new cask package\n";
}

}  // namespace help
