//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

//
// This file implements the help command.

#pragma once

#include <string_view>

namespace help {

void help();
void list();
void unknown_command(std::string_view command);
void new_missing_path();

}  // namespace help
