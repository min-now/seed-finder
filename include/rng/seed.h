#ifndef SEED_FINDER_RNG_SEED_H
#define SEED_FINDER_RNG_SEED_H

#include "config/parameters.h"
#include "utils/types.h"

typedef struct seed_ctx_t {
	u64 seed;

	u64 mac_address;

	bool soft_reset;

	u8  day, month;
	u8  hour, minute, second;
	u16 year;

	u32 keypress;

	const u32 (*nazos)[5];

	u32 timer0, vcount, vframe, gxstat;
} seed_t;

void seed_ctx_init(struct seed_ctx_t *ctx, struct parameters_t *params);

#endif /* SEED_FINDER_RNG_SEED_H */
