//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

#include <catch2/catch_test_macros.hpp>
#include <commands/new.hpp>
#include <utils/fs.hpp>

TEST_CASE("New", "NewProject") {
  const auto path{fs::temp_directory_path()};

  fs::current_path(path);

  new_cmd::run("sandbox");

  REQUIRE(fs::exists(path / "sandbox" / "Cask.toml"));
  REQUIRE(fs::exists(path / "sandbox" / "src" / "main.cpp"));

  fs::remove_all(path / "sandbox");
}