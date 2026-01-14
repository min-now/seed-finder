#ifndef SEED_FINDER_UTILS_MACROS_H
#define SEED_FINDER_UTILS_MACROS_H

#include <stdio.h>
#include <string.h>

#define PRINT_ERROR(S, ...)\
	fprintf(stderr, "error in %s: %s, line: %d\n\t" S "\n", __FILE__, __func__, __LINE__, ##__VA_ARGS__)

#define PRINT_ERROR_ABORT(S, ...) \
	PRINT_ERROR(S, __VA_ARGS__);  \
	exit(1)

#define ROT_L(X, N) (((X) << (N)) | ((X) >> (32 - (N))))
#define ROT_R(X, N) (((X) >> (N)) | ((X) << (32 - (N))))

#define BSWAP(X) __builtin_bswap32((X))

#define CHANGE_ENDIAN(X)                                                \
	(((((X) << 8) & 0xFF00FF00) | (((X) >> 8) & 0xFF00FF)) << 16)       \
		| (((((X) << 8) & 0xFF00FF00) | (((X) >> 8) & 0xFF00FF)) >> 16)

#define STR_EQ(S1, S2) (strcmp((S1), (S2)) == 0)

#endif /* SEED_FINDER_UTILS_MACROS_H */
