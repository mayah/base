#ifndef BASE_COMPILER_SPECIFIC_H_
#define BASE_COMPILER_SPECIFIC_H_

#include "base/build_config.h"

// Annotate the returned value must be used.
// Use like the following:
//  int f() WARN_UNUSED_RESULT;
#ifdef COMPILER_GCC_COMPATIBLE
#  define WARN_UNUSED_RESULT __attribute__((warn_unused_result))
#else
#  define WARN_UNUSED_RESULT
#endif

#endif // BASE_COMPILER_SPECIFIC_H_
