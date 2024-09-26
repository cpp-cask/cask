//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

#pragma once

#include <utils/macro_scope.hpp>

#if CASK_HAS_EXPERIMENTAL_FILESYSTEM
#include <experimental/filesystem>
namespace std_fs = std::experimental::filesystem;
#elif CASK_HAS_FILESYSTEM
#include <filesystem>
namespace std_fs = std::filesystem;
#endif
