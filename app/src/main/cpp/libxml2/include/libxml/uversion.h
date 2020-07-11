// © 2016 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html
/*
*******************************************************************************
*   Copyright (C) 2000-2011, International Business Machines
*   Corporation and others.  All Rights Reserved.
*******************************************************************************
*
*   file name:  uversion.h
*   encoding:   UTF-8
*   tab size:   8 (not used)
*   indentation:4
*
*   Created by: Vladimir Weinstein
*
*  Gets included by utypes.h and Windows .rc files
*/

/*===========================================================================*/
/* Main ICU version information                                              */
/*===========================================================================*/

#ifndef UVERSION_H
#define UVERSION_H

#include "umachine.h"

/* Actual version info lives in uvernum.h */
#include "uvernum.h"

#define U_COPYRIGHT_STRING_LENGTH  128

#define U_MAX_VERSION_LENGTH 4

#define U_VERSION_DELIMITER '.'

#define U_MAX_VERSION_STRING_LENGTH 20

typedef uint8_t UVersionInfo[U_MAX_VERSION_LENGTH];

/*===========================================================================*/
/* C++ namespace if supported. Versioned unless versioning is disabled.      */
/*===========================================================================*/

/* Define C++ namespace symbols. */
#ifdef __cplusplus

#   if U_DISABLE_RENAMING
 #       define U_ICU_NAMESPACE icu
         namespace U_ICU_NAMESPACE { }
 #   else
 #       define U_ICU_NAMESPACE U_ICU_ENTRY_POINT_RENAME(icu)
         namespace U_ICU_NAMESPACE { }
         namespace icu = U_ICU_NAMESPACE;
 #   endif

 #   define U_NAMESPACE_BEGIN namespace U_ICU_NAMESPACE {
 #   define U_NAMESPACE_END }
 #   define U_NAMESPACE_USE using namespace U_ICU_NAMESPACE;
 #   define U_NAMESPACE_QUALIFIER U_ICU_NAMESPACE::

 #   ifndef U_USING_ICU_NAMESPACE
 #       if defined(U_COMBINED_IMPLEMENTATION) || defined(U_COMMON_IMPLEMENTATION) || \
                 defined(U_I18N_IMPLEMENTATION) || defined(U_IO_IMPLEMENTATION) || \
                 defined(U_LAYOUTEX_IMPLEMENTATION) || defined(U_TOOLUTIL_IMPLEMENTATION)
 #           define U_USING_ICU_NAMESPACE 0
 #       else
 #           define U_USING_ICU_NAMESPACE 0
 #       endif
 #   endif
 #   if U_USING_ICU_NAMESPACE
         U_NAMESPACE_USE
 #   endif
#endif /* __cplusplus */

/*===========================================================================*/
/* General version helper functions. Definitions in putil.c                  */
/*===========================================================================*/

U_STABLE void U_EXPORT2
u_versionFromString(UVersionInfo versionArray, const char *versionString);

U_STABLE void U_EXPORT2
u_versionFromUString(UVersionInfo versionArray, const UChar *versionString);


U_STABLE void U_EXPORT2
u_versionToString(const UVersionInfo versionArray, char *versionString);

U_STABLE void U_EXPORT2
u_getVersion(UVersionInfo versionArray);
#endif