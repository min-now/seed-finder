#ifndef SEED_FINDER_UTILS_MACROS_H
#define SEED_FINDER_UTILS_MACROS_H

#include "utils/keypress.h"

#include <stdio.h>

#define PRINT_ERROR(S, ...)                                           \
	fprintf(stderr, "error in %s: %s, line: %d\n\t" S "\n", __FILE__, \
			__func__, __LINE__, ##__VA_ARGS__)

#define ROT_L(X, N) (((X) << (N)) | ((X) >> (32 - (N))))
#define ROT_R(X, N) (((X) >> (N)) | ((X) << (32 - (N))))

#define CHANGE_ENDIAN(X)                                          \
	((((X << 8) & 0xFF00FF00) | ((X >> 8) & 0xFF00FF)) << 16) |   \
		((((X << 8) & 0xFF00FF00) | ((X >> 8) & 0xFF00FF)) >> 16)

#define S1(A, B, C, D, E, I)                     \
	ROT_L(A, 5)                                  \
	+((B & C) | ((~B) & D)) + E + 0x5A827999 + I

#define LOOP_INC(N, X, Y) for (u32 N = X; N <= Y; N++)
#define GENERATE_SEEDS(P, SHA1, CODE)                                      \
	for (size_t kp_idx = 0; kp_idx < KEYPRESS_AMT; kp_idx++) {             \
		if (KEYPRESSES[kp_idx].button_amt > P.max_keypresses) continue;    \
		LOOP_INC(timer0, P.min_timer0, P.max_timer0)                       \
		{                                                                  \
			LOOP_INC(vcount, P.min_vcount, P.max_vcount)                   \
			{                                                              \
				LOOP_INC(vframe, P.min_vframe, P.max_vframe)               \
				{                                                          \
					LOOP_INC(gxstat, P.min_gxstat, P.max_gxstat)           \
					{                                                      \
						LOOP_INC(year, P.min_year, P.max_year)             \
						{                                                  \
							LOOP_INC(month, P.min_month, P.max_month)      \
							{                                              \
								LOOP_INC(day, P.min_day, P.max_day)        \
								{                                          \
									LOOP_INC(hour, P.min_hour, P.max_hour) \
									{                                      \
										LOOP_INC(minute, P.min_minute,     \
												 P.max_minute)             \
										{                                  \
											LOOP_INC(second, P.min_second, \
													 P.max_second)         \
											{                              \
												CODE;                      \
											}                              \
										}                                  \
									}                                      \
								}                                          \
							}                                              \
						}                                                  \
					}                                                      \
				}                                                          \
			}                                                              \
		}                                                                  \
	}

#endif /* SEED_FINDER_UTILS_MACROS_H */
