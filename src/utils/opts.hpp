//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

//
// This file implements a lightweight options parser.

#pragma once

#include <optional>
#include <string>

namespace opts {

enum class Command { Build, Help, List, New, Run };

namespace command {
Command from_str(const std::string_view str);
}

}  // namespace opts
