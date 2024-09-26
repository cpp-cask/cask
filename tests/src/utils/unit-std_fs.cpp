//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

#include <catch2/catch_test_macros.hpp>
#include <utils/std_fs.hpp>

TEST_CASE("StdFs", "WorksInAllPlatforms") {
  std_fs::current_path(std_fs::temp_directory_path());

  // Basic usage
  std_fs::create_directories("sandbox/1/2/a");
  std_fs::create_directory("sandbox/1/2/b");

  // Directory already exists (false returned, no error)
  REQUIRE(!std_fs::create_directory("sandbox/1/2/b"));

  std_fs::remove_all("sandbox");
}