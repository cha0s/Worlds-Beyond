#ifndef CHI_GLOBAL_H
#define CHI_GLOBAL_H

#include <assert.h>
#include <iostream>

#include "stddef.h"

/**
 * @addtogroup Misc
 * @{
 */

#ifdef __GNUC__
#define CHI_TYPEOF __typeof__
#endif

/** Macro to clean up dead code to keep warnings down about unused parameters. */
#ifdef __GNUC__
#define CHI_UNUSED(__var) { \
	const CHI_TYPEOF(__var) *p__var = &__var; \
	p__var = p__var; \
}
#endif

// Stack frame alignment madness for bunk GCC versions on Windows x86.
#if defined(_WIN32)
#  define CHI_ENSURE_STACK_ALIGNED_FOR_SSE __attribute__ ((force_align_arg_pointer))
#else
#  define CHI_ENSURE_STACK_ALIGNED_FOR_SSE
#endif

/**
 * @}
 */

#endif // CHI_GLOBAL_H
