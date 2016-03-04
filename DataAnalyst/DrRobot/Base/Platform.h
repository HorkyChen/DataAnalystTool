/*
 * Copyright (C) 2011 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */
//  Created by Chen Hao on 8/17/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.

#ifndef DataAnalyst_Platform_h
#define DataAnalyst_Platform_h
/* COMPILER() - the compiler being used to build the project */
#define COMPILER(FEATURE) (defined COMPILER_##FEATURE  && COMPILER_##FEATURE)

/* COMPILER_SUPPORTS() - whether the compiler being used to build the project supports the given feature. */
#define COMPILER_SUPPORTS(COMPILER_FEATURE) (defined COMPILER_SUPPORTS_##COMPILER_FEATURE  && COMPILER_SUPPORTS_##COMPILER_FEATURE)


#if defined(__clang__)
#define COMPILER_CLANG 1

#ifndef __has_extension
#define __has_extension __has_feature /* Compatibility with older versions of clang */
#endif

/* Specific compiler features */
#define COMPILER_SUPPORTS_CXX_VARIADIC_TEMPLATES __has_feature(cxx_variadic_templates)
#define COMPILER_SUPPORTS_CXX_RVALUE_REFERENCES __has_feature(cxx_rvalue_references)
#define COMPILER_SUPPORTS_CXX_DELETED_FUNCTIONS __has_feature(cxx_deleted_functions)
#define COMPILER_SUPPORTS_CXX_NULLPTR __has_feature(cxx_nullptr)
#define COMPILER_SUPPORTS_BLOCKS __has_feature(blocks)
#endif


/* COMPILER(MSVC) - Microsoft Visual C++ */
/* COMPILER(MSVC7_OR_LOWER) - Microsoft Visual C++ 2003 or lower*/
/* COMPILER(MSVC9_OR_LOWER) - Microsoft Visual C++ 2008 or lower*/
#if defined(_MSC_VER)
#define COMPILER_MSVC 1
#if _MSC_VER < 1400
#define COMPILER_MSVC7_OR_LOWER 1
#elif _MSC_VER < 1600
#define COMPILER_MSVC9_OR_LOWER 1
#endif

/* Specific compiler features */
#if _MSC_VER >= 1600
#define COMPILER_SUPPORTS_CXX_NULLPTR 1
#endif

#endif

/* COMPILER(RVCT) - ARM RealView Compilation Tools */
/* COMPILER(RVCT4_OR_GREATER) - ARM RealView Compilation Tools 4.0 or greater */
#if defined(__CC_ARM) || defined(__ARMCC__)
#define COMPILER_RVCT 1
#define RVCT_VERSION_AT_LEAST(major, minor, patch, build) (__ARMCC_VERSION >= (major * 100000 + minor * 10000 + patch * 1000 + build))
#else
/* Define this for !RVCT compilers, just so we can write things like RVCT_VERSION_AT_LEAST(3, 0, 0, 0). */
#define RVCT_VERSION_AT_LEAST(major, minor, patch, build) 0
#endif

/* COMPILER(GCCE) - GNU Compiler Collection for Embedded */
#if defined(__GCCE__)
#define COMPILER_GCCE 1
#define GCCE_VERSION (__GCCE__ * 10000 + __GCCE_MINOR__ * 100 + __GCCE_PATCHLEVEL__)
#define GCCE_VERSION_AT_LEAST(major, minor, patch) (GCCE_VERSION >= (major * 10000 + minor * 100 + patch))
#endif

/* COMPILER(GCC) - GNU Compiler Collection */
/* --gnu option of the RVCT compiler also defines __GNUC__ */
#if defined(__GNUC__) && !COMPILER(RVCT)
#define COMPILER_GCC 1
#define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#define GCC_VERSION_AT_LEAST(major, minor, patch) (GCC_VERSION >= (major * 10000 + minor * 100 + patch))

/* Specific compiler features */
#if !COMPILER(CLANG) && GCC_VERSION_AT_LEAST(4, 6, 0) && defined(__GXX_EXPERIMENTAL_CXX0X__)
#define COMPILER_SUPPORTS_CXX_NULLPTR 1 
#endif

#else
/* Define this for !GCC compilers, just so we can write things like GCC_VERSION_AT_LEAST(4, 1, 0). */
#define GCC_VERSION_AT_LEAST(major, minor, patch) 0
#endif


#ifndef ALWAYS_INLINE
#if COMPILER(GCC) && defined(NDEBUG) && !COMPILER(MINGW)
#define ALWAYS_INLINE inline __attribute__((__always_inline__))
#elif (COMPILER(MSVC) || COMPILER(RVCT)) && defined(NDEBUG)
#define ALWAYS_INLINE __forceinline
#else
#define ALWAYS_INLINE inline
#endif
#endif

/* NEVER_INLINE */

#ifndef NEVER_INLINE
#if COMPILER(GCC)
#define NEVER_INLINE __attribute__((__noinline__))
#elif COMPILER(RVCT)
#define NEVER_INLINE __declspec(noinline)
#else
#define NEVER_INLINE
#endif
#endif


/* UNLIKELY */

#ifndef UNLIKELY
#if COMPILER(GCC) || (RVCT_VERSION_AT_LEAST(3, 0, 0, 0) && defined(__GNUC__))
#define UNLIKELY(x) __builtin_expect((x), 0)
#else
#define UNLIKELY(x) (x)
#endif
#endif


/* LIKELY */

#ifndef LIKELY
#if COMPILER(GCC) || (RVCT_VERSION_AT_LEAST(3, 0, 0, 0) && defined(__GNUC__))
#define LIKELY(x) __builtin_expect((x), 1)
#else
#define LIKELY(x) (x)
#endif
#endif


/* NO_RETURN */


#ifndef NO_RETURN
#if COMPILER(GCC)
#define NO_RETURN __attribute((__noreturn__))
#elif COMPILER(MSVC) || COMPILER(RVCT)
#define NO_RETURN __declspec(noreturn)
#else
#define NO_RETURN
#endif
#endif


/* NO_RETURN_WITH_VALUE */

#ifndef NO_RETURN_WITH_VALUE
#if !COMPILER(MSVC)
#define NO_RETURN_WITH_VALUE NO_RETURN
#else
#define NO_RETURN_WITH_VALUE
#endif
#endif


/* WARN_UNUSED_RETURN */

#if COMPILER(GCC)
#define WARN_UNUSED_RETURN __attribute__ ((warn_unused_result))
#else
#define WARN_UNUSED_RETURN
#endif

/* OVERRIDE */

#ifndef OVERRIDE
#if COMPILER(CLANG)
#if __has_extension(cxx_override_control)
#define OVERRIDE override
#endif
#elif COMPILER(MSVC)
#define OVERRIDE override
#endif
#endif

#ifndef OVERRIDE
#define OVERRIDE
#endif

/* FINAL */

#ifndef FINAL
#if COMPILER(CLANG)
#if __has_extension(cxx_override_control)
#define FINAL final
#endif
#elif COMPILER(MSVC)
#define FINAL sealed
#endif
#endif

#ifndef FINAL
#define FINAL
#endif

#endif
