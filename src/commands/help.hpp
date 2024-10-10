//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

//
// This file implements the help command.

#pragma once

#include <fmt/color.h>

#include <span>
#include <string_view>

namespace help {

constexpr fmt::color blue{fmt::color::deep_sky_blue};
constexpr fmt::color green{fmt::color::light_green};
constexpr fmt::color red{fmt::color::red};

void run();
void run(const std::span<char *> args);
void list();
void fatal_error(const std::string_view msg);

}  // namespace help
