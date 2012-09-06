#ifndef WB_GLOBAL_H
#define WB_GLOBAL_H

#include <assert.h>
#include <iostream>

#include "stddef.h"

/**
 * @addtogroup Misc
 * @{
 */

#ifdef __GNUC__
#define WB_TYPEOF __typeof__
#endif

/** Macro to clean up dead code to keep warnings down about unused parameters. */
#ifdef __GNUC__
#define WB_UNUSED(__var) { \
	const WB_TYPEOF(__var) *p__var = &__var; \
	p__var = p__var; \
}
#endif

// Stack frame alignment madness for bunk GCC versions on Windows x86.
#if defined(_WIN32)
#  define WB_ENSURE_STACK_ALIGNED_FOR_SSE __attribute__ ((force_align_arg_pointer))
#else
#  define WB_ENSURE_STACK_ALIGNED_FOR_SSE
#endif

/**
 * @}
 */

#endif // WB_GLOBAL_H
