//              Copyright Cask Authors
// Distributed under the Boost Software License, Version 1.0.
//   (See accompanying file LICENSE.txt or copy at
//        https://www.boost.org/LICENSE_1_0.txt)

// SPDX-License-Identifier: BSL-1.0

#pragma once

// This file contains all internal macro definitions

#if !defined(CASK_HAS_FILESYSTEM) && !defined(CASK_HAS_EXPERIMENTAL_FILESYSTEM)
#if defined(__cpp_lib_filesystem)
#define CASK_HAS_FILESYSTEM 1
#elif defined(__cpp_lib_experimental_filesystem)
#define CASK_HAS_EXPERIMENTAL_FILESYSTEM 1
#elif !defined(__has_include)
#define CASK_HAS_EXPERIMENTAL_FILESYSTEM 1
#elif __has_include(<filesystem>)
#define CASK_HAS_FILESYSTEM 1
#elif __has_include(<experimental/filesystem>)
#define CASK_HAS_EXPERIMENTAL_FILESYSTEM 1
#endif

#ifndef CASK_HAS_EXPERIMENTAL_FILESYSTEM
#define CASK_HAS_EXPERIMENTAL_FILESYSTEM 0
#endif

#ifndef CASK_HAS_FILESYSTEM
#define CASK_HAS_FILESYSTEM 0
#endif
#endif
