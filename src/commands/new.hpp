//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

//
// This file implements the help command.

#ifndef SRC_COMMANDS_NEW_HPP_
#define SRC_COMMANDS_NEW_HPP_

#include <string_view>

namespace new_cmd {

void run(std::string_view project_name);

}  // namespace new_cmd

#endif  // SRC_COMMANDS_NEW_HPP_
