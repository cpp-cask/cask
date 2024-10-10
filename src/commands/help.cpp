//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

//
// This file implements the help command.

#include <fmt/core.h>

#include <commands/help.hpp>
#include <iostream>
#include <utils/opts.hpp>

namespace help {

void run() {
  fmt::print(
      R"(C++'s package manager

{} {}

{}
    {}  Compile the current package
    {}    Create a new cask package
    {}    Run a binary or example of the local package

See '{} {}' for more information on a specific command.
)",
      fmt::format(fg(green) | fmt::emphasis::bold, "Usage:"),
      fmt::format(fg(blue) | fmt::emphasis::bold, "cask [COMMAND]"),
      fmt::format(fg(green) | fmt::emphasis::bold, "Commands:"),
      fmt::format(fg(blue) | fmt::emphasis::bold, "build"),
      fmt::format(fg(blue) | fmt::emphasis::bold, "new"),
      fmt::format(fg(blue) | fmt::emphasis::bold, "run"),
      fmt::format(fg(blue) | fmt::emphasis::bold, "cask help"),
      fmt::format(fg(blue), "<command>"));
}

void run(const std::span<char *> args) {
  if (args.empty()) {
    run();
    return;
  }

  const auto command{opts::command::from_str(args[0])};

  switch (command) {
    case opts::Command::Add: {
      fmt::print(R"(Add MAN PAGE)");
      break;
    }
    case opts::Command::Help: {
      fmt::print(R"(HELP MAN PAGE)");
      break;
    }
    case opts::Command::List: {
      fmt::print(R"(List MAN PAGE)");
      help::list();
      break;
    }
    case opts::Command::New: {
      fmt::print(R"(NAME
       cask-new — Create a new Cask package
SYNOPSIS
       cask new path

DESCRIPTION
       This command will create a new Cask package in the given directory. This includes a simple template with a Cask.toml manifest, sample source file, and a VCS ignore file. If the directory is not already in a VCS repository, then a new repository is created (see --vcs below).

       See cask-init(1) for a similar command which will create a new manifest in an existing directory.
)");
      break;
    }
    case opts::Command::Build: {
      fmt::print(R"(Build MAN PAGE)");
      break;
    }
    case opts::Command::Run: {
      fmt::print(R"(Fmt MAN PAGE)");
      break;
    }
  }
}

void list() {
  fmt::print(R"(Installed Commands:
  build                Compile a local package and all of its dependencies
  help                 Displays help for a cask subcommand
  new                  Create a new cask package at <path>
  run                  Run a binary or example of the local package)");
}

void fatal_error(const std::string_view msg) {
  fmt::print(R"({} {})", fmt::format(fg(red) | fmt::emphasis::bold, "error:"),
             msg);
}

}  // namespace help
