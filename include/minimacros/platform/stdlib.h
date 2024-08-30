#pragma once

#include <minimacros/utils/common.h>

// C++ stadnard library detection.
//
// Strings:
//   Name: M_STRING_CPP_STDLIB
//   Version: M_STRING_CPP_STDLIB_VERSION
//   Version date: M_VERSION_CPP_STDLIB_DATE -  libstdc++: YYYYmmDD; MSVC STL: YYYYmm (then 'L'), libc++: empty (M_HAVE_VERSION_CPP_STDLIB_DATE == 0)
//
// Version numbers:
//   M_VERSION_CPP_STDLIB - libstdc++: major version; libc++: 6 digits: 2 major, 2 minor, 2 patch; MSVC STL: 3 digits (14x)
//   M_VERSION_CPP_STDLIB_SHORT - libc++: major version, everywhere else same as M_VERSION_CPP_STDLIB
//
// Version number checks: (always false if wrong stdlib)
//   M_IS_LIBSTDCXX_VERSION(== 14)   M_IS_LIBSTDCXX_DATE(== YYYYmmDD)
//   M_IS_LIBCXX_VERSION(== 18)      M_IS_LIBCPP_VERSION_FULL(== 180100)
//   M_IS_MSVC_STL_VERSION(== 143)   M_IS_MSVC_STL_DATE(== 202308)

#if __has_include(<version>)
#include <version>
#else
#include <ciso646> // Removed in C++20. `<iso646.h>` doesn't define the C++ macros.
#endif

#if defined(_GLIBCXX_RELEASE)
#  define M_IS_LIBSTDCXX 1
#  define M_STRING_CPP_STDLIB "libstdc++"
#  define M_HAVE_VERSION_CPP_STDLIB 1
#  define M_HAVE_VERSION_CPP_STDLIB_DATE 1
#  define M_VERSION_CPP_STDLIB_SHORT _GLIBCXX_RELEASE
#  define M_VERSION_CPP_STDLIB _GLIBCXX_RELEASE
#  define M_VERSION_CPP_STDLIB_DATE __GLIBCXX__
#  define M_STRING_CPP_STDLIB_VERSION M_STR(M_VERSION_CPP_STDLIB)
#  define M_STRING_CPP_STDLIB_DATE M_STR(M_VERSION_CPP_STDLIB_DATE)
#  define M_IS_LIBSTDCXX_VERSION(...) (M_VERSION_CPP_STDLIB __VA_ARGS__)
#  define M_IS_LIBSTDCXX_DATE(...) (M_VERSION_CPP_STDLIB_DATE __VA_ARGS__)
#elif defined(_LIBCPP_VERSION)
#  define M_IS_LIBCPP 1
#  define M_STRING_CPP_STDLIB "libc++"
#  define M_HAVE_VERSION_CPP_STDLIB 1
#  define M_HAVE_VERSION_CPP_STDLIB_DATE 0
#  define M_VERSION_CPP_STDLIB_SHORT (_LIBCPP_VERSION / 10000)
#  define M_VERSION_CPP_STDLIB _LIBCPP_VERSION
#  define M_VERSION_CPP_STDLIB_DATE 0
#  define M_STRING_CPP_STDLIB_VERSION M_STR(M_VERSION_CPP_STDLIB)
#  define M_STRING_CPP_STDLIB_DATE "-"
#  define M_IS_LIBCPP_VERSION(...) (M_VERSION_CPP_STDLIB_SHORT __VA_ARGS__)
#  define M_IS_LIBCPP_VERSION_FULL(...) (M_VERSION_CPP_STDLIB __VA_ARGS__)
#elif defined(_MSVC_STL_VERSION)
#  define M_IS_MSVC_STL 1
#  define M_STRING_CPP_STDLIB "MSVC STL"
#  define M_HAVE_VERSION_CPP_STDLIB 1
#  define M_HAVE_VERSION_CPP_STDLIB_DATE 1
#  define M_VERSION_CPP_STDLIB_SHORT _MSVC_STL_VERSION
#  define M_VERSION_CPP_STDLIB _MSVC_STL_VERSION
#  define M_VERSION_CPP_STDLIB_DATE _MSVC_STL_UPDATE
#  define M_STRING_CPP_STDLIB_VERSION M_STR(M_VERSION_CPP_STDLIB)
#  define M_STRING_CPP_STDLIB_DATE M_STR(M_VERSION_CPP_STDLIB_DATE)
#  define M_IS_MSVC_STL_VERSION(...) (M_VERSION_CPP_STDLIB __VA_ARGS__)
#  define M_IS_MSVC_STL_DATE(...) (M_VERSION_CPP_STDLIB_DATE __VA_ARGS__)
#else
#  define M_STRING_CPP_STDLIB "Unknown C++ standard library"
#  define M_HAVE_VERSION_CPP_STDLIB 0
#  define M_HAVE_VERSION_CPP_STDLIB_DATE 0
#  define M_VERSION_CPP_STDLIB_SHORT 0
#  define M_VERSION_CPP_STDLIB 0
#  define M_VERSION_CPP_STDLIB_DATE 0
#  define M_STRING_CPP_STDLIB_VERSION "-"
#  define M_STRING_CPP_STDLIB_DATE "-"
#endif

#ifndef M_IS_LIBCPP
#define M_IS_LIBCPP 0
#endif
#ifndef M_IS_LIBCPP_VERSION
#define M_IS_LIBCPP_VERSION(...) 0
#endif
#ifndef M_IS_LIBCPP_VERSION_FULL
#define M_IS_LIBCPP_VERSION_FULL(...) 0
#endif
#ifndef M_IS_LIBSTDCXX
#define M_IS_LIBSTDCXX 0
#endif
#ifndef M_IS_LIBSTDCXX_DATE
#define M_IS_LIBSTDCXX_DATE(...) 0
#endif
#ifndef M_IS_LIBSTDCXX_VERSION
#define M_IS_LIBSTDCXX_VERSION(...) 0
#endif
#ifndef M_IS_MSVC_STL
#define M_IS_MSVC_STL 0
#endif
#ifndef M_IS_MSVC_STL_DATE
#define M_IS_MSVC_STL_DATE(...) 0
#endif
#ifndef M_IS_MSVC_STL_VERSION
#define M_IS_MSVC_STL_VERSION(...) 0
#endif
