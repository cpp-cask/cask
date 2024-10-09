//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

#include <array>
#include <catch2/catch_test_macros.hpp>
#include <commands/new.hpp>
#include <filesystem>

namespace fs = std::filesystem;

TEST_CASE("New", "NewProject") {
  const auto path{fs::temp_directory_path()};

  fs::current_path(path);

  SECTION("New") {
    const char* arg1 = "sandbox";
    char* argv[] = {const_cast<char*>(arg1)};
    int argc = sizeof(argv) / sizeof(argv[0]);

    new_cmd::run(std::span(argv, argc));

    REQUIRE(fs::exists(path / "sandbox" / "Cask.toml"));
    REQUIRE(fs::exists(path / "sandbox" / "src" / "main.cpp"));
  }

  SECTION("CleanUp") { fs::remove_all(path / "sandbox"); }
}