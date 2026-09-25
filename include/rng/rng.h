#ifndef SEED_FINDER_RNG_RNG_H
#define SEED_FINDER_RNG_RNG_H

#include <stdlib.h>

#include "locale/version.h"
#include "utils/types.h"

typedef struct rng_s {
	u64 seed, rng;

	size_t frame;

	void (*print)(struct rng_s *rng);

	void (*reset)(struct rng_s *rng);
	void (*reseed)(struct rng_s *rng, u64 seed);

	u64 (*rand)(const struct rng_s *rng, u32 x);

	u64 (*adv)(struct rng_s *rng, size_t n);
	u64 (*adv_rand)(struct rng_s *rng, size_t n, u32 x);

	u64 (*next)(struct rng_s *rng);
	u64 (*next_rand)(struct rng_s *rng, u32 x);

	u64 (*peek)(const struct rng_s *rng, size_t n);
	u64 (*peek_rand)(const struct rng_s *rng, size_t n, u32 x);

	u64 (*init_adv)(struct rng_s *rng);
} rng_t;

rng_t rng_init(u64 seed, version_t version);

void rng_reset(rng_t *rng);
void rng_reseed(rng_t *, u64 seed);

u64 rng_rand(const rng_t *rng, u32 x);

u64 rng_adv(rng_t *rng, size_t n);
u64 rng_adv_rand(rng_t *rng, size_t n, u32 x);

u64 rng_next(rng_t *rng);
u64 rng_next_rand(rng_t *rng, u32 x);

u64 rng_peek(const rng_t *rng, size_t n);
u64 rng_peek_rand(const rng_t *rng, size_t n, u32 x);

u64 rng_init_adv_bw1(rng_t *rng);
u64 rng_init_adv_bw2(rng_t *rng);

#endif /* SEED_FINDER_RNG_RNG_H */
