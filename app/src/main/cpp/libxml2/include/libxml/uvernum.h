// © 2016 and later: Unicode, Inc. and others.
// License & terms of use: http://www.unicode.org/copyright.html
/*
*******************************************************************************
*   Copyright (C) 2000-2016, International Business Machines
*   Corporation and others.  All Rights Reserved.
*******************************************************************************
*
*   file name:  uvernum.h
*   encoding:   UTF-8
*   tab size:   8 (not used)
*   indentation:4
*
*   Created by: Vladimir Weinstein
*   Updated by: Steven R. Loomis
*
*/

/*
 * IMPORTANT: When updating version, the following things need to be done:
 * source/common/unicode/uvernum.h - this file: update major, minor,
 *        patchlevel, suffix, version, short version constants, namespace,
 *                    renaming macro, and copyright
 *
 * The following files need to be updated as well, which can be done
 *  by running the UNIX makefile target 'update-windows-makefiles' in icu/source.
 *
 *
 * source/common/common_uwp.vcxproj
 * source/common/common.vcxproj - update 'Output file name' on the link tab so
 *                   that it contains the new major/minor combination
 * source/i18n/i18n.vcxproj - same as for the common.vcxproj
 * source/i18n/i18n_uwp.vcxproj - same as for the common_uwp.vcxproj
 * source/layoutex/layoutex.vcproj - same
 * source/stubdata/stubdata.vcproj - same as for the common.vcxproj
 * source/io/io.vcproj - same as for the common.vcxproj
 * source/data/makedata.mak - change U_ICUDATA_NAME so that it contains
 *                            the new major/minor combination and the Unicode version.
 */

#ifndef UVERNUM_H
#define UVERNUM_H

#define U_COPYRIGHT_STRING \
   " Copyright (C) 2016 and later: Unicode, Inc. and others. License & terms of use: http://www.unicode.org/copyright.html "

#define U_ICU_VERSION_MAJOR_NUM 67

#define U_ICU_VERSION_MINOR_NUM 1

#define U_ICU_VERSION_PATCHLEVEL_NUM 0

#ifndef U_ICU_VERSION_BUILDLEVEL_NUM
#define U_ICU_VERSION_BUILDLEVEL_NUM 0
#endif

#define U_ICU_VERSION_SUFFIX _67

#ifndef U_DISABLE_VERSION_SUFFIX
#define U_DISABLE_VERSION_SUFFIX 0
#endif

#ifndef U_ICU_ENTRY_POINT_RENAME
#ifdef U_HAVE_LIB_SUFFIX
#   if !U_DISABLE_VERSION_SUFFIX
 #       define U_DEF_ICU_ENTRY_POINT_RENAME(x,y,z) x ## y ##  z
 #       define U_DEF2_ICU_ENTRY_POINT_RENAME(x,y,z) U_DEF_ICU_ENTRY_POINT_RENAME(x,y,z)
 #       define U_ICU_ENTRY_POINT_RENAME(x)    U_DEF2_ICU_ENTRY_POINT_RENAME(x,U_ICU_VERSION_SUFFIX,U_LIB_SUFFIX_C_NAME)
 #   else
 #       define U_DEF_ICU_ENTRY_POINT_RENAME(x,y) x ## y
 #       define U_DEF2_ICU_ENTRY_POINT_RENAME(x,y) U_DEF_ICU_ENTRY_POINT_RENAME(x,y)
 #       define U_ICU_ENTRY_POINT_RENAME(x)    U_DEF2_ICU_ENTRY_POINT_RENAME(x,U_LIB_SUFFIX_C_NAME)
 #   endif
#else
#   if !U_DISABLE_VERSION_SUFFIX
#       define U_DEF_ICU_ENTRY_POINT_RENAME(x,y) x ## y
#       define U_DEF2_ICU_ENTRY_POINT_RENAME(x,y) U_DEF_ICU_ENTRY_POINT_RENAME(x,y)
#       define U_ICU_ENTRY_POINT_RENAME(x)    U_DEF2_ICU_ENTRY_POINT_RENAME(x,U_ICU_VERSION_SUFFIX)
#   else
#       define U_ICU_ENTRY_POINT_RENAME(x)    x
#   endif
#endif
#endif

#define U_ICU_VERSION "67.1"

#define U_ICU_VERSION_SHORT "67"

#ifndef U_HIDE_INTERNAL_API

#define U_ICU_DATA_VERSION "67.1"
#endif  /* U_HIDE_INTERNAL_API */

/*===========================================================================
 * ICU collation framework version information
 * Version info that can be obtained from a collator is affected by these
 * numbers in a secret and magic way. Please use collator version as whole
 *===========================================================================
 */

#define UCOL_RUNTIME_VERSION 9

#define UCOL_BUILDER_VERSION 9

#ifndef U_HIDE_DEPRECATED_API

#define UCOL_TAILORINGS_VERSION 1
#endif  /* U_HIDE_DEPRECATED_API */

#endif