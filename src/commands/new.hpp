//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

//
// This file implements the help command.

#pragma once

#include <span>
#include <string_view>

namespace new_cmd {

void run(const std::span<char *> args);

}  // namespace new_cmd
