#ifndef SEED_FINDER_UTILS_MACROS_H
#define SEED_FINDER_UTILS_MACROS_H

#include <stdio.h>

#define PRINT_ERROR(S)                                                         \
	fprintf(stderr, "%s: %s.%d - %s", __FILE__, __func__, __LINE__, (S))

#endif /* SEED_FINDER_UTILS_MACROS_H */
