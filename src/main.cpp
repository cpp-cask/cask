//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

//
// This file implements the Cask functionality.

#include <commands/build.hpp>
#include <commands/help.hpp>
#include <commands/new.hpp>
#include <commands/run.hpp>
#include <span>
#include <string_view>
#include <utils/opts.hpp>
#include <vector>

namespace {
const std::span<char*> cmd_args(const std::span<char*> args) {
  return {args.data() + 1, args.size() - 1};
}
}  // namespace

int main(int ac, char* av[]) {
  const auto args = std::span(av, ac);

  if (args.empty()) {
    help::run();
    exit(EXIT_FAILURE);
  }

  const auto command{opts::command::from_str(args.at(0))};

  switch (command) {
    case opts::Command::Help: {
      help::run();
      break;
    }
    case opts::Command::List: {
      help::list();
      break;
    }
    case opts::Command::New: {
      new_cmd::run(cmd_args(args));
      break;
    }
    case opts::Command::Build: {
      build::run();
      break;
    }
    case opts::Command::Run: {
      run::run();
      break;
    }
  }

  return 0;
}
