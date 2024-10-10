//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

//
// This file implements the add command.

#pragma once

#include <span>
#include <string_view>

namespace add {

void run(const std::span<char *> args);

}  // namespace add
