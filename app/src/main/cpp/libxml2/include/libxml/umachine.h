// © 2016 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html
/*
******************************************************************************
*
*   Copyright (C) 1999-2015, International Business Machines
*   Corporation and others.  All Rights Reserved.
*
******************************************************************************
*   file name:  umachine.h
*   encoding:   UTF-8
*   tab size:   8 (not used)
*   indentation:4
*
*   created on: 1999sep13
*   created by: Markus W. Scherer
*
*   This file defines basic types and constants for ICU to be
*   platform-independent. umachine.h and utf.h are included into
*   utypes.h to provide all the general definitions for ICU.
*   All of these definitions used to be in utypes.h before
*   the UTF-handling macros made this unmaintainable.
*/

#ifndef __UMACHINE_H__
#define __UMACHINE_H__


/*==========================================================================*/
/* Include platform-dependent definitions                                   */
/* which are contained in the platform-specific file platform.h             */
/*==========================================================================*/

#include "ptypes.h" /* platform.h is included in ptypes.h */

/*
 * ANSI C headers:
 * stddef.h defines wchar_t
 */
#include <stddef.h>

/*==========================================================================*/
/* For C wrappers, we use the symbol U_STABLE.                                */
/* This works properly if the includer is C or C++.                         */
/* Functions are declared   U_STABLE return-type U_EXPORT2 function-name()... */
/*==========================================================================*/

#ifdef __cplusplus
#   define U_CFUNC extern "C"
 #   define U_CDECL_BEGIN extern "C" {
 #   define U_CDECL_END   }
#else
#   define U_CFUNC extern
#   define U_CDECL_BEGIN
#   define U_CDECL_END
#endif

#ifndef U_ATTRIBUTE_DEPRECATED

#if U_GCC_MAJOR_MINOR >= 302
#    define U_ATTRIBUTE_DEPRECATED __attribute__ ((deprecated))

#elif defined(_MSC_VER) && (_MSC_VER >= 1400)
#    define U_ATTRIBUTE_DEPRECATED __declspec(deprecated)
#else
#    define U_ATTRIBUTE_DEPRECATED
#endif
#endif

#define U_CAPI U_CFUNC U_EXPORT

#define U_STABLE U_CAPI

#define U_DRAFT  U_CAPI

#define U_DEPRECATED U_CAPI U_ATTRIBUTE_DEPRECATED

#define U_OBSOLETE U_CAPI

#define U_INTERNAL U_CAPI

#ifndef U_OVERRIDE
#define U_OVERRIDE override
#endif

#if !defined(U_FINAL) || defined(U_IN_DOXYGEN)
#define U_FINAL final
#endif

// Before ICU 65, function-like, multi-statement ICU macros were just defined as
// series of statements wrapped in { } blocks and the caller could choose to
// either treat them as if they were actual functions and end the invocation
// with a trailing ; creating an empty statement after the block or else omit
// this trailing ; using the knowledge that the macro would expand to { }.
//
// But doing so doesn't work well with macros that look like functions and
// compiler warnings about empty statements (ICU-20601) and ICU 65 therefore
// switches to the standard solution of wrapping such macros in do { } while.
//
// This will however break existing code that depends on being able to invoke
// these macros without a trailing ; so to be able to remain compatible with
// such code the wrapper is itself defined as macros so that it's possible to
// build ICU 65 and later with the old macro behaviour, like this:
//
// export CPPFLAGS='-DUPRV_BLOCK_MACRO_BEGIN="" -DUPRV_BLOCK_MACRO_END=""'
// runConfigureICU ...
//

#ifndef UPRV_BLOCK_MACRO_BEGIN
#define UPRV_BLOCK_MACRO_BEGIN do
#endif

#ifndef UPRV_BLOCK_MACRO_END
#define UPRV_BLOCK_MACRO_END while (FALSE)
#endif

/*==========================================================================*/
/* limits for int32_t etc., like in POSIX inttypes.h                        */
/*==========================================================================*/

#ifndef INT8_MIN

#   define INT8_MIN        ((int8_t)(-128))
#endif
#ifndef INT16_MIN

#   define INT16_MIN       ((int16_t)(-32767-1))
#endif
#ifndef INT32_MIN

#   define INT32_MIN       ((int32_t)(-2147483647-1))
#endif

#ifndef INT8_MAX

#   define INT8_MAX        ((int8_t)(127))
#endif
#ifndef INT16_MAX

#   define INT16_MAX       ((int16_t)(32767))
#endif
#ifndef INT32_MAX

#   define INT32_MAX       ((int32_t)(2147483647))
#endif

#ifndef UINT8_MAX

#   define UINT8_MAX       ((uint8_t)(255U))
#endif
#ifndef UINT16_MAX

#   define UINT16_MAX      ((uint16_t)(65535U))
#endif
#ifndef UINT32_MAX

#   define UINT32_MAX      ((uint32_t)(4294967295U))
#endif

#if defined(U_INT64_T_UNAVAILABLE)
# error int64_t is required for decimal format and rule-based number format.
#else
# ifndef INT64_C

#   define INT64_C(c) c ## LL
# endif
# ifndef UINT64_C

#   define UINT64_C(c) c ## ULL
# endif
# ifndef U_INT64_MIN

#     define U_INT64_MIN       ((int64_t)(INT64_C(-9223372036854775807)-1))
# endif
# ifndef U_INT64_MAX

#     define U_INT64_MAX       ((int64_t)(INT64_C(9223372036854775807)))
# endif
# ifndef U_UINT64_MAX

#     define U_UINT64_MAX      ((uint64_t)(UINT64_C(18446744073709551615)))
# endif
#endif

/*==========================================================================*/
/* Boolean data type                                                        */
/*==========================================================================*/

typedef int8_t UBool;

#ifndef TRUE

#   define TRUE  1
#endif
#ifndef FALSE

#   define FALSE 0
#endif


/*==========================================================================*/
/* Unicode data types                                                       */
/*==========================================================================*/

/* wchar_t-related definitions -------------------------------------------- */

/*
 * \def U_WCHAR_IS_UTF16
 * Defined if wchar_t uses UTF-16.
 *
 * @stable ICU 2.0
 */
/*
 * \def U_WCHAR_IS_UTF32
 * Defined if wchar_t uses UTF-32.
 *
 * @stable ICU 2.0
 */
#if !defined(U_WCHAR_IS_UTF16) && !defined(U_WCHAR_IS_UTF32)
#   ifdef __STDC_ISO_10646__
#       if (U_SIZEOF_WCHAR_T==2)
 #           define U_WCHAR_IS_UTF16
 #       elif (U_SIZEOF_WCHAR_T==4)
 #           define  U_WCHAR_IS_UTF32
 #       endif
#   elif defined __UCS2__
#       if (U_PF_OS390 <= U_PLATFORM && U_PLATFORM <= U_PF_OS400) && (U_SIZEOF_WCHAR_T==2)
 #           define U_WCHAR_IS_UTF16
 #       endif
#   elif defined(__UCS4__) || (U_PLATFORM == U_PF_OS400 && defined(__UTF32__))
#       if (U_SIZEOF_WCHAR_T==4)
 #           define U_WCHAR_IS_UTF32
 #       endif
#   elif U_PLATFORM_IS_DARWIN_BASED || (U_SIZEOF_WCHAR_T==4 && U_PLATFORM_IS_LINUX_BASED)
#       define U_WCHAR_IS_UTF32
#   elif U_PLATFORM_HAS_WIN32_API
#       define U_WCHAR_IS_UTF16
#   endif
#endif

/* UChar and UChar32 definitions -------------------------------------------- */

#define U_SIZEOF_UCHAR 2

#if (U_PLATFORM == U_PF_AIX) && defined(__cplusplus) &&(U_CPLUSPLUS_VERSION < 11)
// for AIX, uchar.h needs to be included
 # include <uchar.h>
 # define U_CHAR16_IS_TYPEDEF 1
#elif defined(_MSC_VER) && (_MSC_VER < 1900)
// Versions of Visual Studio/MSVC below 2015 do not support char16_t as a real type,
 // and instead use a typedef.  https://msdn.microsoft.com/library/bb531344.aspx
 # define U_CHAR16_IS_TYPEDEF 1
#else
# define U_CHAR16_IS_TYPEDEF 0
#endif


#if 1
// #if 1 is normal. UChar defaults to char16_t in C++.
// For configuration testing of UChar=uint16_t temporarily change this to #if 0.
// The intltest Makefile #defines UCHAR_TYPE=char16_t,
// so we only #define it to uint16_t if it is undefined so far.
#elif !defined(UCHAR_TYPE)
#   define UCHAR_TYPE uint16_t
#endif

#if defined(U_COMBINED_IMPLEMENTATION) || defined(U_COMMON_IMPLEMENTATION) || \
         defined(U_I18N_IMPLEMENTATION) || defined(U_IO_IMPLEMENTATION)
// Inside the ICU library code, never configurable.
     typedef char16_t UChar;
#elif defined(UCHAR_TYPE)
typedef UCHAR_TYPE UChar;
#elif (U_CPLUSPLUS_VERSION >= 11)
typedef char16_t UChar;
#else
typedef uint16_t UChar;
#endif

#if U_SIZEOF_WCHAR_T==2
typedef wchar_t OldUChar;
#elif defined(__CHAR16_TYPE__)
typedef __CHAR16_TYPE__ OldUChar;
#else
typedef uint16_t OldUChar;
#endif

typedef int32_t UChar32;

#define U_SENTINEL (-1)

#include "urename.h"

#endif