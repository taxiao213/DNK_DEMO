// © 2016 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html
/*
******************************************************************************
*
*   Copyright (C) 1997-2016, International Business Machines
*   Corporation and others.  All Rights Reserved.
*
******************************************************************************
*
*  FILE NAME : platform.h
*
*   Date        Name        Description
*   05/13/98    nos         Creation (content moved here from ptypes.h).
*   03/02/99    stephen     Added AS400 support.
*   03/30/99    stephen     Added Linux support.
*   04/13/99    stephen     Reworked for autoconf.
******************************************************************************
*/

#ifndef _PLATFORM_H
#define _PLATFORM_H

#include "uconfig.h"
#include "uvernum.h"

#ifdef U_IN_DOXYGEN
/*
  * Problem: "platform.h:335: warning: documentation for unknown define U_HAVE_STD_STRING found." means that U_HAVE_STD_STRING is not documented.
  * Solution: #define any defines for non @internal API here, so that they are visible in the docs.  If you just set PREDEFINED in Doxyfile.in,  they won't be documented.
  */

 /* None for now. */
#endif

#define U_PF_UNKNOWN 0

#define U_PF_WINDOWS 1000

#define U_PF_MINGW 1800

#define U_PF_CYGWIN 1900
/* Reserve 2000 for U_PF_UNIX? */
#define U_PF_HPUX 2100

#define U_PF_SOLARIS 2600

#define U_PF_BSD 3000

#define U_PF_AIX 3100

#define U_PF_IRIX 3200

#define U_PF_DARWIN 3500

#define U_PF_IPHONE 3550

#define U_PF_QNX 3700

#define U_PF_LINUX 4000

#define U_PF_BROWSER_NATIVE_CLIENT 4020

#define U_PF_ANDROID 4050

#define U_PF_FUCHSIA 4100
/* Maximum value for Linux-based platform is 4499 */
#define U_PF_EMSCRIPTEN 5010

#define U_PF_OS390 9000

#define U_PF_OS400 9400

#ifdef U_PLATFORM
/* Use the predefined value. */
#elif defined(__MINGW32__)
#   define U_PLATFORM U_PF_MINGW
#elif defined(__CYGWIN__)
#   define U_PLATFORM U_PF_CYGWIN
#elif defined(WIN32) || defined(_WIN32) || defined(WIN64) || defined(_WIN64)
#   define U_PLATFORM U_PF_WINDOWS
#elif defined(__ANDROID__)
#   define U_PLATFORM U_PF_ANDROID
     /* Android wchar_t support depends on the API level. */
 #   include <android/api-level.h>
#elif defined(__pnacl__) || defined(__native_client__)
#   define U_PLATFORM U_PF_BROWSER_NATIVE_CLIENT
#elif defined(__Fuchsia__)
#   define U_PLATFORM U_PF_FUCHSIA
#elif defined(linux) || defined(__linux__) || defined(__linux)
#   define U_PLATFORM U_PF_LINUX
#elif defined(__APPLE__) && defined(__MACH__)
#   include <TargetConditionals.h>
 #   if defined(TARGET_OS_IPHONE) && TARGET_OS_IPHONE  /* variant of TARGET_OS_MAC */
 #       define U_PLATFORM U_PF_IPHONE
 #   else
 #       define U_PLATFORM U_PF_DARWIN
 #   endif
#elif defined(BSD) || defined(__FreeBSD__) || defined(__FreeBSD_kernel__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__MirBSD__)
#   if defined(__FreeBSD__)
 #       include <sys/endian.h>
 #   endif
 #   define U_PLATFORM U_PF_BSD
#elif defined(sun) || defined(__sun)
/* Check defined(__SVR4) || defined(__svr4__) to distinguish Solaris from SunOS? */
 #   define U_PLATFORM U_PF_SOLARIS
 #   if defined(__GNUC__)
         /* Solaris/GCC needs this header file to get the proper endianness. Normally, this
          * header file is included with stddef.h but on Solairs/GCC, the GCC version of stddef.h
          *  is included which does not include this header file.
          */
 #       include <sys/isa_defs.h>
 #   endif
#elif defined(_AIX) || defined(__TOS_AIX__)
#   define U_PLATFORM U_PF_AIX
#elif defined(_hpux) || defined(hpux) || defined(__hpux)
#   define U_PLATFORM U_PF_HPUX
#elif defined(sgi) || defined(__sgi)
#   define U_PLATFORM U_PF_IRIX
#elif defined(__QNX__) || defined(__QNXNTO__)
#   define U_PLATFORM U_PF_QNX
#elif defined(__TOS_MVS__)
#   define U_PLATFORM U_PF_OS390
#elif defined(__OS400__) || defined(__TOS_OS400__)
#   define U_PLATFORM U_PF_OS400
#elif defined(__EMSCRIPTEN__)
#   define U_PLATFORM U_PF_EMSCRIPTEN
#else
#   define U_PLATFORM U_PF_UNKNOWN
#endif

/* Commented out because this is already set in mh-cygwin-msvc
#if U_PLATFORM == U_PF_CYGWIN && defined(_MSC_VER)
#   define CYGWINMSVC
#endif
*/
#ifdef U_IN_DOXYGEN
#   define CYGWINMSVC
#endif

#ifdef U_PLATFORM_USES_ONLY_WIN32_API
/* Use the predefined value. */
#elif (U_PF_WINDOWS <= U_PLATFORM && U_PLATFORM <= U_PF_MINGW) || defined(CYGWINMSVC)
#   define U_PLATFORM_USES_ONLY_WIN32_API 1
#else
/* Cygwin implements POSIX. */
#   define U_PLATFORM_USES_ONLY_WIN32_API 0
#endif

#ifdef U_PLATFORM_HAS_WIN32_API
/* Use the predefined value. */
#elif U_PF_WINDOWS <= U_PLATFORM && U_PLATFORM <= U_PF_CYGWIN
#   define U_PLATFORM_HAS_WIN32_API 1
#else
#   define U_PLATFORM_HAS_WIN32_API 0
#endif

#ifdef U_PLATFORM_HAS_WINUWP_API
/* Use the predefined value. */
#else
#   define U_PLATFORM_HAS_WINUWP_API 0
#endif

#ifdef U_PLATFORM_IMPLEMENTS_POSIX
/* Use the predefined value. */
#elif U_PLATFORM_USES_ONLY_WIN32_API
#   define U_PLATFORM_IMPLEMENTS_POSIX 0
#else
#   define U_PLATFORM_IMPLEMENTS_POSIX 1
#endif

#ifdef U_PLATFORM_IS_LINUX_BASED
/* Use the predefined value. */
#elif U_PF_LINUX <= U_PLATFORM && U_PLATFORM <= 4499
#   define U_PLATFORM_IS_LINUX_BASED 1
#else
#   define U_PLATFORM_IS_LINUX_BASED 0
#endif

#ifdef U_PLATFORM_IS_DARWIN_BASED
/* Use the predefined value. */
#elif U_PF_DARWIN <= U_PLATFORM && U_PLATFORM <= U_PF_IPHONE
#   define U_PLATFORM_IS_DARWIN_BASED 1
#else
#   define U_PLATFORM_IS_DARWIN_BASED 0
#endif

#ifdef U_HAVE_STDINT_H
/* Use the predefined value. */
#elif U_PLATFORM_USES_ONLY_WIN32_API
#   if defined(__BORLANDC__) || U_PLATFORM == U_PF_MINGW || (defined(_MSC_VER) && _MSC_VER>=1600)
         /* Windows Visual Studio 9 and below do not have stdint.h & inttypes.h, but VS 2010 adds them. */
 #       define U_HAVE_STDINT_H 1
 #   else
 #       define U_HAVE_STDINT_H 0
 #   endif
#elif U_PLATFORM == U_PF_SOLARIS
/* Solaris has inttypes.h but not stdint.h. */
 #   define U_HAVE_STDINT_H 0
#elif U_PLATFORM == U_PF_AIX && !defined(_AIX51) && defined(_POWER)
/* PPC AIX <= 4.3 has inttypes.h but not stdint.h. */
 #   define U_HAVE_STDINT_H 0
#else
#   define U_HAVE_STDINT_H 1
#endif

#ifdef U_HAVE_INTTYPES_H
/* Use the predefined value. */
#elif U_PLATFORM == U_PF_SOLARIS
/* Solaris has inttypes.h but not stdint.h. */
 #   define U_HAVE_INTTYPES_H 1
#elif U_PLATFORM == U_PF_AIX && !defined(_AIX51) && defined(_POWER)
/* PPC AIX <= 4.3 has inttypes.h but not stdint.h. */
 #   define U_HAVE_INTTYPES_H 1
#else
/* Most platforms have both inttypes.h and stdint.h, or neither. */
#   define U_HAVE_INTTYPES_H U_HAVE_STDINT_H
#endif

/*===========================================================================*/
/*===========================================================================*/

#ifdef __GNUC__
#   define U_GCC_MAJOR_MINOR (__GNUC__ * 100 + __GNUC_MINOR__)
#else
#   define U_GCC_MAJOR_MINOR 0
#endif

#ifdef U_IS_BIG_ENDIAN
/* Use the predefined value. */
#elif defined(BYTE_ORDER) && defined(BIG_ENDIAN)
#   define U_IS_BIG_ENDIAN (BYTE_ORDER == BIG_ENDIAN)
#elif defined(__BYTE_ORDER__) && defined(__ORDER_BIG_ENDIAN__)
/* gcc */
 #   define U_IS_BIG_ENDIAN (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#elif defined(__BIG_ENDIAN__) || defined(_BIG_ENDIAN)
#   define U_IS_BIG_ENDIAN 1
#elif defined(__LITTLE_ENDIAN__) || defined(_LITTLE_ENDIAN)
#   define U_IS_BIG_ENDIAN 0
#elif U_PLATFORM == U_PF_OS390 || U_PLATFORM == U_PF_OS400 || defined(__s390__) || defined(__s390x__)
/* These platforms do not appear to predefine any endianness macros. */
 #   define U_IS_BIG_ENDIAN 1
#elif defined(_PA_RISC1_0) || defined(_PA_RISC1_1) || defined(_PA_RISC2_0)
/* HPPA do not appear to predefine any endianness macros. */
 #   define U_IS_BIG_ENDIAN 1
#elif defined(sparc) || defined(__sparc) || defined(__sparc__)
/* Some sparc based systems (e.g. Linux) do not predefine any endianness macros. */
 #   define U_IS_BIG_ENDIAN 1
#else
#   define U_IS_BIG_ENDIAN 0
#endif

#ifdef U_HAVE_PLACEMENT_NEW
/* Use the predefined value. */
#elif defined(__BORLANDC__)
#   define U_HAVE_PLACEMENT_NEW 0
#else
#   define U_HAVE_PLACEMENT_NEW 1
#endif

#ifdef U_HAVE_DEBUG_LOCATION_NEW
/* Use the predefined value. */
#elif defined(_MSC_VER)
#   define U_HAVE_DEBUG_LOCATION_NEW 1
#else
#   define U_HAVE_DEBUG_LOCATION_NEW 0
#endif

/* Compatibility with compilers other than clang: http://clang.llvm.org/docs/LanguageExtensions.html */
#ifdef __has_attribute
#   define UPRV_HAS_ATTRIBUTE(x) __has_attribute(x)
#else
#   define UPRV_HAS_ATTRIBUTE(x) 0
#endif
#ifdef __has_cpp_attribute
#   define UPRV_HAS_CPP_ATTRIBUTE(x) __has_cpp_attribute(x)
#else
#   define UPRV_HAS_CPP_ATTRIBUTE(x) 0
#endif
#ifdef __has_declspec_attribute
#   define UPRV_HAS_DECLSPEC_ATTRIBUTE(x) __has_declspec_attribute(x)
#else
#   define UPRV_HAS_DECLSPEC_ATTRIBUTE(x) 0
#endif
#ifdef __has_builtin
#   define UPRV_HAS_BUILTIN(x) __has_builtin(x)
#else
#   define UPRV_HAS_BUILTIN(x) 0
#endif
#ifdef __has_feature
#   define UPRV_HAS_FEATURE(x) __has_feature(x)
#else
#   define UPRV_HAS_FEATURE(x) 0
#endif
#ifdef __has_extension
#   define UPRV_HAS_EXTENSION(x) __has_extension(x)
#else
#   define UPRV_HAS_EXTENSION(x) 0
#endif
#ifdef __has_warning
#   define UPRV_HAS_WARNING(x) __has_warning(x)
#else
#   define UPRV_HAS_WARNING(x) 0
#endif

#if defined(__GNUC__) && __GNUC__>=3
#    define U_MALLOC_ATTR __attribute__ ((__malloc__))
#else
#    define U_MALLOC_ATTR
#endif

#if (defined(__GNUC__) &&                                            \
         (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 3))) || \
         UPRV_HAS_ATTRIBUTE(alloc_size)
#   define U_ALLOC_SIZE_ATTR(X) __attribute__ ((alloc_size(X)))
 #   define U_ALLOC_SIZE_ATTR2(X,Y) __attribute__ ((alloc_size(X,Y)))
#else
#   define U_ALLOC_SIZE_ATTR(X)
#   define U_ALLOC_SIZE_ATTR2(X,Y)
#endif

#ifdef U_CPLUSPLUS_VERSION
#   if U_CPLUSPLUS_VERSION != 0 && !defined(__cplusplus)
 #       undef U_CPLUSPLUS_VERSION
 #       define U_CPLUSPLUS_VERSION 0
 #   endif
     /* Otherwise use the predefined value. */
#elif !defined(__cplusplus)
#   define U_CPLUSPLUS_VERSION 0
#elif __cplusplus >= 201402L || (defined(_MSVC_LANG) && _MSVC_LANG >= 201402L)
#   define U_CPLUSPLUS_VERSION 14
 #elif __cplusplus >= 201103L || (defined(_MSVC_LANG) && _MSVC_LANG >= 201103L)
 #   define U_CPLUSPLUS_VERSION 11
 #else
     // C++98 or C++03
 #   define U_CPLUSPLUS_VERSION 1
#endif

#if (U_PLATFORM == U_PF_AIX || U_PLATFORM == U_PF_OS390) && defined(__cplusplus) &&(U_CPLUSPLUS_VERSION < 11)
// add in std::nullptr_t
 namespace std {
   typedef decltype(nullptr) nullptr_t;
 };
#endif

#ifdef U_NOEXCEPT
/* Use the predefined value. */
#else
#   define U_NOEXCEPT noexcept
#endif

#ifndef __cplusplus
// Not for C.
#elif defined(U_FALLTHROUGH)
// Use the predefined value.
 #elif defined(__clang__)
     // Test for compiler vs. feature separately.
     // Other compilers might choke on the feature test.
 #    if UPRV_HAS_CPP_ATTRIBUTE(clang::fallthrough) || \
              (UPRV_HAS_FEATURE(cxx_attributes) &&     \
              UPRV_HAS_WARNING("-Wimplicit-fallthrough"))
 #       define U_FALLTHROUGH [[clang::fallthrough]]
 #   endif
 #elif defined(__GNUC__) && (__GNUC__ >= 7)
 #   define U_FALLTHROUGH __attribute__((fallthrough))
#endif

#ifndef U_FALLTHROUGH
#   define U_FALLTHROUGH
#endif

/*===========================================================================*/
/*===========================================================================*/

#define U_ASCII_FAMILY 0

#define U_EBCDIC_FAMILY 1

#ifdef U_CHARSET_FAMILY
/* Use the predefined value. */
#elif U_PLATFORM == U_PF_OS390 && (!defined(__CHARSET_LIB) || !__CHARSET_LIB)
#   define U_CHARSET_FAMILY U_EBCDIC_FAMILY
#elif U_PLATFORM == U_PF_OS400 && !defined(__UTF32__)
#   define U_CHARSET_FAMILY U_EBCDIC_FAMILY
#else
#   define U_CHARSET_FAMILY U_ASCII_FAMILY
#endif

#ifdef U_CHARSET_IS_UTF8
/* Use the predefined value. */
#elif U_PLATFORM_IS_LINUX_BASED || U_PLATFORM_IS_DARWIN_BASED || \
         U_PLATFORM == U_PF_EMSCRIPTEN
#   define U_CHARSET_IS_UTF8 1
#else
#   define U_CHARSET_IS_UTF8 0
#endif

/*===========================================================================*/
/*===========================================================================*/

#ifdef U_HAVE_WCHAR_H
/* Use the predefined value. */
#elif U_PLATFORM == U_PF_ANDROID && __ANDROID_API__ < 9
/*
      * Android before Gingerbread (Android 2.3, API level 9) did not support wchar_t.
      * The type and header existed, but the library functions did not work as expected.
      * The size of wchar_t was 1 but L"xyz" string literals had 32-bit units anyway.
      */
 #   define U_HAVE_WCHAR_H 0
#else
#   define U_HAVE_WCHAR_H 1
#endif

#ifdef U_SIZEOF_WCHAR_T
/* Use the predefined value. */
#elif (U_PLATFORM == U_PF_ANDROID && __ANDROID_API__ < 9)
/*
      * Classic Mac OS and Mac OS X before 10.3 (Panther) did not support wchar_t or wstring.
      * Newer Mac OS X has size 4.
      */
 #   define U_SIZEOF_WCHAR_T 1
#elif U_PLATFORM_HAS_WIN32_API || U_PLATFORM == U_PF_CYGWIN
#   define U_SIZEOF_WCHAR_T 2
#elif U_PLATFORM == U_PF_AIX
/*
      * AIX 6.1 information, section "Wide character data representation":
      * "... the wchar_t datatype is 32-bit in the 64-bit environment and
      * 16-bit in the 32-bit environment."
      * and
      * "All locales use Unicode for their wide character code values (process code),
      * except the IBM-eucTW codeset."
      */
 #   ifdef __64BIT__
 #       define U_SIZEOF_WCHAR_T 4
 #   else
 #       define U_SIZEOF_WCHAR_T 2
 #   endif
#elif U_PLATFORM == U_PF_OS390
/*
      * z/OS V1R11 information center, section "LP64 | ILP32":
      * "In 31-bit mode, the size of long and pointers is 4 bytes and the size of wchar_t is 2 bytes.
      * Under LP64, the size of long and pointer is 8 bytes and the size of wchar_t is 4 bytes."
      */
 #   ifdef _LP64
 #       define U_SIZEOF_WCHAR_T 4
 #   else
 #       define U_SIZEOF_WCHAR_T 2
 #   endif
#elif U_PLATFORM == U_PF_OS400
#   if defined(__UTF32__)
         /*
          * LOCALETYPE(*LOCALEUTF) is specified.
          * Wide-character strings are in UTF-32,
          * narrow-character strings are in UTF-8.
          */
 #       define U_SIZEOF_WCHAR_T 4
 #   elif defined(__UCS2__)
         /*
          * LOCALETYPE(*LOCALEUCS2) is specified.
          * Wide-character strings are in UCS-2,
          * narrow-character strings are in EBCDIC.
          */
 #       define U_SIZEOF_WCHAR_T 2
 #   else
         /*
          * LOCALETYPE(*CLD) or LOCALETYPE(*LOCALE) is specified.
          * Wide-character strings are in 16-bit EBCDIC,
          * narrow-character strings are in EBCDIC.
          */
 #       define U_SIZEOF_WCHAR_T 2
 #   endif
#else
#   define U_SIZEOF_WCHAR_T 4
#endif

#ifndef U_HAVE_WCSCPY
#define U_HAVE_WCSCPY U_HAVE_WCHAR_H
#endif

#ifdef U_HAVE_CHAR16_T
/* Use the predefined value. */
#else
/*
 * Notes:
 * Visual Studio 2010 (_MSC_VER==1600) defines char16_t as a typedef
 * and does not support u"abc" string literals.
 * Visual Studio 2015 (_MSC_VER>=1900) and above adds support for
 * both char16_t and u"abc" string literals.
 * gcc 4.4 defines the __CHAR16_TYPE__ macro to a usable type but
 * does not support u"abc" string literals.
 * C++11 and C11 require support for UTF-16 literals
 * TODO: Fix for plain C. Doesn't work on Mac.
 */
#   if U_CPLUSPLUS_VERSION >= 11 || (defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L)
#       define U_HAVE_CHAR16_T 1
#   else
#       define U_HAVE_CHAR16_T 0
#   endif
#endif

#ifdef U_DECLARE_UTF16
/* Use the predefined value. */
#elif U_HAVE_CHAR16_T \
     || (defined(__xlC__) && defined(__IBM_UTF_LITERAL) && U_SIZEOF_WCHAR_T != 2) \
     || (defined(__HP_aCC) && __HP_aCC >= 035000) \
     || (defined(__HP_cc) && __HP_cc >= 111106) \
     || (defined(U_IN_DOXYGEN))
#   define U_DECLARE_UTF16(string) u ## string
#elif U_SIZEOF_WCHAR_T == 2 \
     && (U_CHARSET_FAMILY == 0 || (U_PF_OS390 <= U_PLATFORM && U_PLATFORM <= U_PF_OS400 && defined(__UCS2__)))
#   define U_DECLARE_UTF16(string) L ## string
#else
/* Leave U_DECLARE_UTF16 undefined. See unistr.h. */
#endif

/*===========================================================================*/
/*===========================================================================*/

#ifdef U_EXPORT
/* Use the predefined value. */
#elif defined(U_STATIC_IMPLEMENTATION)
#   define U_EXPORT
#elif defined(_MSC_VER) || (UPRV_HAS_DECLSPEC_ATTRIBUTE(dllexport) && \
                             UPRV_HAS_DECLSPEC_ATTRIBUTE(dllimport))
#   define U_EXPORT __declspec(dllexport)
#elif defined(__GNUC__)
#   define U_EXPORT __attribute__((visibility("default")))
#elif (defined(__SUNPRO_CC) && __SUNPRO_CC >= 0x550) \
    || (defined(__SUNPRO_C) && __SUNPRO_C >= 0x550)
#   define U_EXPORT __global
 /*#elif defined(__HP_aCC) || defined(__HP_cc)
 #   define U_EXPORT __declspec(dllexport)*/
#else
#   define U_EXPORT
#endif

/* U_CALLCONV is related to U_EXPORT2 */
#ifdef U_EXPORT2
/* Use the predefined value. */
#elif defined(_MSC_VER)
#   define U_EXPORT2 __cdecl
#else
#   define U_EXPORT2
#endif

#ifdef U_IMPORT
/* Use the predefined value. */
#elif defined(_MSC_VER) || (UPRV_HAS_DECLSPEC_ATTRIBUTE(dllexport) && \
                             UPRV_HAS_DECLSPEC_ATTRIBUTE(dllimport))
/* Windows needs to export/import data. */
 #   define U_IMPORT __declspec(dllimport)
#else
#   define U_IMPORT
#endif

#if U_PLATFORM == U_PF_OS390 && defined(__cplusplus)
#    define U_CALLCONV __cdecl
#else
#    define U_CALLCONV U_EXPORT2
#endif

#if U_PLATFORM == U_PF_OS390 && defined(__cplusplus)
#    define U_CALLCONV_FPTR U_CALLCONV
#else
#    define U_CALLCONV_FPTR
#endif
/* @} */

#endif  // _PLATFORM_H