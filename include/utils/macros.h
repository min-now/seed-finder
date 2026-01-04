#ifndef SEED_FINDER_UTILS_MACROS_H
#define SEED_FINDER_UTILS_MACROS_H

#include <stdio.h>

#define PRINT_ERROR(S, ...)                                           \
	fprintf(stderr, "error in %s: %s, line: %d\n\t" S "\n", __FILE__, \
			__func__, __LINE__, ##__VA_ARGS__)

#endif /* SEED_FINDER_UTILS_MACROS_H */
