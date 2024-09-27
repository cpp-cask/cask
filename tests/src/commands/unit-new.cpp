//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

#include <catch2/catch_test_macros.hpp>
#include <commands/new.hpp>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("New", "NewProject") {
  const auto path{fs::temp_directory_path()};

  fs::current_path(path);

  new_cmd::run("sandbox-new");

  REQUIRE(fs::exists(path / "sandbox-new" / "Cask.toml"));
  REQUIRE(fs::exists(path / "sandbox-new" / "src" / "main.cpp"));

  std::filesystem::permissions(path / "sandbox-new",
                               std::filesystem::perms::owner_write |
                                   std::filesystem::perms::group_write |
                                   std::filesystem::perms::others_write,
                               std::filesystem::perm_options::add);

  fs::remove_all(path / "sandbox-new");
}