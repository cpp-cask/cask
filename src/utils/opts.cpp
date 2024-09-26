//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

#include <optional>
#include <string>
#include <unordered_map>
#include <utils/opts.hpp>

namespace opts::command {

std::optional<Command> from_str(const std::string& str) {
  static const std::unordered_map<std::string, Command> command_map{
      {"--help", Command::Help},
      {"help", Command::Help},
      {"--list", Command::List},
      {"new", Command::New},
      {"run", Command::Run}};

  if (auto it{command_map.find(str)}; it != command_map.end()) {
    return it->second;
  } else {
    return std::nullopt;
  }
}

}  // namespace opts::command
