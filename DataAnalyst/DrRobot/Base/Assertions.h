//
//  Assertions.h
//  DataAnalyst
//
//  Created by Chen Hao on 8/16/14.
//  Copyright (c) 2014 PoxenStudio. All rights reserved.
//

#ifndef DataAnalyst_Assertions_h
#define DataAnalyst_Assertions_h

#ifdef __cplusplus
extern "C" {
#endif

#ifndef CRASH
#if defined(__clang__)
#define CRASH() do { \
*(int *)0xbaadbeef = 0; \
__builtin_trap(); \
} while (false)
#else
#define CRASH() do { \
*(int *)0xbaadbeef = 0; \
((void(*)())0)(); /* More reliable, but doesn't say BBADBEEF */ \
} while (false)
#endif

#define ASSERT(assertion) do \
if (!(assertion)) { \
CRASH(); \
} \
while (0)

#ifndef COMPILE_ASSERT
#define COMPILE_ASSERT(exp, name) typedef int dummy##name [(exp) ? 1 : -1]
#endif
#ifdef __cplusplus
}
#endif

#endif
#endif

