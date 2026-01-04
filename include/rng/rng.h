#ifndef SEED_FINDER_RNG_RNG_H
#define SEED_FINDER_RNG_RNG_H

#include "locale/language.h"
#include "utils/types.h"

static const u8 RNG_ADVANCEMENT_TABLE[5][4] = {{50, 100, 100, 100},
											   {50, 50, 100, 100},
											   {30, 50, 100, 100},
											   {25, 30, 50, 100},
											   {20, 25, 33, 50}};

struct rng_t
{
	u64 seed;
	u64 rng;
	u32 frame;

	u64 (*adv)(struct rng_t *rng, u32 amt);
	u64 (*next)(struct rng_t *rng);
	u64 (*rand)(const struct rng_t *rng, u32 num);
	u64 (*rand_next)(struct rng_t *rng, u32 num);
	u64 (*init_adv)(struct rng_t *rng);

	void (*reset)(struct rng_t *rng);
};

struct rng_t rng_init(u64 seed, enum game_version_e version);

u64 rng_adv(struct rng_t *rng, u32 amt);

u64 rng_next(struct rng_t *rng);

u64 rng_rand(const struct rng_t *rng, u32 num);

u64 rng_rand_next(struct rng_t *rng, u32 num);

u64 rng_init_adv_bw1(struct rng_t *rng);

u64 rng_init_adv_bw2(struct rng_t *rng);

void rng_reset(struct rng_t *rng);

#endif /* SEED_FINDER_RNG_RNG_H */
