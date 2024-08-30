#pragma once

#include <minimacros/utils/common.h>

// Compiler detection.
//
// * GCC:                 M_IS_GCC_LIKE   M_IS_ACTUAL_GCC
// * Clang:               M_IS_GCC_LIKE   M_IS_CLANG        M_IS_CLANG_MSVC
// * Clang in MSVC mode:  M_IS_MSVC_LIKE  M_IS_CLANG        M_IS_CLANG_NON_MSVC
// * MSVC:                M_IS_MSVC_LIKE  M_IS_ACTUAL_MSVC
//
// Strings:
//   M_STRING_COMPILER                         - name
//   M_STRING_COMPILER_VERSION{,_SHORT,_LONG}  - name with version (GCC/Clang: X.Y.Z, _SHORT: only X, _LONG: with date (GCC) or commit hash (Clang); MSVC: 19XX, _SHORT: same, _LONG: 19XXyyyyy).
//
// Version number:
//   M_VERSION_COMPILER:
//     For GCC and Clang, 6 digits: 2 major, 2 minor, 2 patchlevel.
//     For MSVC, 4+5 digits: 19XXyyyyy
//   M_VERSION_COMPILER_MAJOR:
//     For GCC and Clang, just the major number.
//     For MSVC, 4 digits: 19XX
//
// Version number checks: (always false if wrong compiler)
//   M_IS_GCC_VERSION(== 14)           M_IS_CLANG_VERSION(== 18)           M_IS_MSVC_VERSION(== 1938)
//   M_IS_GCC_VERSION_FULL(== 140201)  M_IS_CLANG_VERSION_FULL(== 180105)  M_IS_MSVC_VERSION_FULL(== 193833133)
//   Can use any comparison operator, not only `==`.


// Compiler name.
#if defined(_MSC_VER)
#  define M_IS_MSVC_LIKE 1
#  ifdef __clang__
#    define M_STRING_COMPILER "Clang (in MSVC mode)"
#    define M_IS_CLANG 1
#    define M_IS_CLANG_MSVC 1
#  else
#    define M_STRING_COMPILER "MSVC"
#    define M_IS_ACTUAL_MSVC 1
#  endif
#elif defined(__GNUC__)
#  define M_IS_GCC_LIKE 1
#  ifdef __clang__
#    ifdef _WIN32
#      define M_STRING_COMPILER "Clang (MinGW)"
#    else
#      define M_STRING_COMPILER "Clang"
#    endif
#    define M_IS_CLANG 1
#    define M_IS_CLANG_NON_MSVC 1
#  else
#    define M_STRING_COMPILER "GCC"
#    define M_IS_ACTUAL_GCC 1
#  endif
#else
#  define M_STRING_COMPILER "Unknown compiler"
#endif

#ifndef M_IS_ACTUAL_GCC
#define M_IS_ACTUAL_GCC 0
#endif
#ifndef M_IS_ACTUAL_MSVC
#define M_IS_ACTUAL_MSVC 0
#endif
#ifndef M_IS_CLANG
#define M_IS_CLANG 0
#endif
#ifndef M_IS_CLANG
#define M_IS_CLANG 0
#endif
#ifndef M_IS_CLANG_MSVC
#define M_IS_CLANG_MSVC 0
#endif
#ifndef M_IS_CLANG_NON_MSVC
#define M_IS_CLANG_NON_MSVC 0
#endif
#ifndef M_IS_GCC_LIKE
#define M_IS_GCC_LIKE 0
#endif
#ifndef M_IS_MSVC_LIKE
#define M_IS_MSVC_LIKE 0
#endif

// Version:
#if defined(__clang__)
#  define M_HAVE_VERSION_COMPILER 1
#  define M_STRING_COMPILER_VERSION_SHORT M_STR(__clang_major__)
#  define M_STRING_COMPILER_VERSION M_STR(__clang_major__) "." M_STR(__clang_minor__) "." M_STR(__clang_patchlevel__)
#  define M_STRING_COMPILER_VERSION_LONG __clang_version__
#  define M_VERSION_COMPILER (__clang_major__ * 10000 + __clang_minor__ * 100 + __clang_patchlevel__)
#  define M_VERSION_COMPILER_MAJOR __clang_major__
#  define M_IS_CLANG_VERSION(...) (M_VERSION_COMPILER_MAJOR __VA_ARGS__)
#  define M_IS_CLANG_VERSION_FULL(...) (M_VERSION_COMPILER __VA_ARGS__)
#elif defined(__GNUC__)
// Can't reuse this in Clang, because there it reports an ancient GCC version.
#  define M_HAVE_VERSION_COMPILER 1
#  define M_STRING_COMPILER_VERSION_SHORT M_STR(__GNUC__)
#  define M_STRING_COMPILER_VERSION M_STR(__GNUC__) "." M_STR(__GNUC_MINOR__) "." M_STR(__GNUC_PATCHLEVEL__)
#  define M_STRING_COMPILER_VERSION_LONG __VERSION__
#  define M_VERSION_COMPILER (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#  define M_VERSION_COMPILER_MAJOR __GNUC__
#  define M_IS_GCC_VERSION(...) (M_VERSION_COMPILER_MAJOR __VA_ARGS__)
#  define M_IS_GCC_VERSION_FULL(...) (M_VERSION_COMPILER __VA_ARGS__)
#elif defined(_MSC_VER)
#  define M_HAVE_VERSION_COMPILER 1
#  define M_STRING_COMPILER_VERSION_SHORT M_STR(_MSC_VER)
#  define M_STRING_COMPILER_VERSION M_STR(_MSC_VER)
#  define M_STRING_COMPILER_VERSION_LONG M_STR(_MSC_FULL_VER)
#  define M_VERSION_COMPILER _MSC_FULL_VER
#  define M_VERSION_COMPILER_MAJOR _MSC_VER // Same
#  define M_IS_MSVC_VERSION(...) (M_VERSION_COMPILER_MAJOR __VA_ARGS__)
#  define M_IS_MSVC_VERSION_FULL(...) (M_VERSION_COMPILER __VA_ARGS__)
// Don't need `M_IS_MSVC_VERSION`.
#else
#  define M_HAVE_VERSION_COMPILER 0
#  define M_STRING_COMPILER_VERSION_SHORT "-"
#  define M_STRING_COMPILER_VERSION "-.-.-"
#  define M_STRING_COMPILER_VERSION_LONG "-.-.-"
#  define M_VERSION_COMPILER 0
#  define M_VERSION_COMPILER_MAJOR 0
#endif

#ifndef M_IS_CLANG_VERSION
#define M_IS_CLANG_VERSION(...) 0
#endif
#ifndef M_IS_CLANG_VERSION_FULL
#define M_IS_CLANG_VERSION_FULL(...) 0
#endif
#ifndef M_IS_GCC_VERSION
#define M_IS_GCC_VERSION(...) 0
#endif
#ifndef M_IS_GCC_VERSION_FULL
#define M_IS_GCC_VERSION_FULL(...) 0
#endif
#ifndef M_IS_MSVC_VERSION
#define M_IS_MSVC_VERSION(...) 0
#endif
#ifndef M_IS_MSVC_VERSION_FULL
#define M_IS_MSVC_VERSION_FULL(...) 0
#endif
