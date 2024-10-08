//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

#include <fmt/core.h>

#include <commands/help.hpp>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utils/opts.hpp>

namespace opts::command {

namespace {
void unknown_command(std::string_view command) {
  help::fatal_error(fmt::format(R"(no such command: `{}`

       Did you mean `help`

       View all installed commands with `cask --list`
)",
                                command));
}
}  // namespace

Command from_str(const std::string_view str) {
  static const std::unordered_map<std::string_view, Command> command_map{
      {"--help", Command::Help}, {"help", Command::Help},
      {"--list", Command::List}, {"new", Command::New},
      {"run", Command::Run},     {"build", Command::Build}};

  if (auto it{command_map.find(str)}; it != command_map.end()) {
    return it->second;
  } else {
    unknown_command(str);
    exit(EXIT_FAILURE);
  }
}

}  // namespace opts::command
