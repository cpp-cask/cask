//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

#include <catch2/catch_test_macros.hpp>
#include <commands/new.hpp>
#include <commands/run.hpp>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("Run", "RunProject") {
  const auto path{fs::temp_directory_path()};

  fs::current_path(path);

  new_cmd::run("sandbox-run");

  REQUIRE(fs::exists(path / "sandbox-run" / "Cask.toml"));
  REQUIRE(fs::exists(path / "sandbox-run" / "src" / "main.cpp"));

  fs::current_path(path / "sandbox-run");

  run::run("sandbox-run");

  std::filesystem::permissions(path / "sandbox-run",
                               std::filesystem::perms::owner_write |
                                   std::filesystem::perms::group_write |
                                   std::filesystem::perms::others_write,
                               std::filesystem::perm_options::add);

  fs::remove_all(path / "sandbox-run");

  // std::uintmax_t n{fs::remove_all(tmp / "abcdef")};
  //   std::cout << "Deleted " << n << " files or directories\n";

  // fs::current_path(path);

  // new_cmd::run("sandbox");

  // REQUIRE(fs::exists(path / "sandbox" / "Cask.toml"));
  // REQUIRE(fs::exists(path / "sandbox" / "src" / "main.cpp"));

  // fs::current_path(path / "sandbox");

  // run::run("sandbox");

  // REQUIRE(fs::exists(path / "target" / "debug" / "CMakeLists.txt"));
  // // REQUIRE(fs::exists(path / "target" / "debug" / "build" / "Makefile"));

  // fs::remove_all("sandbox");
}