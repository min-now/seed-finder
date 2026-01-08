#ifndef SEED_FINDER_RNG_SHA1_H
#define SEED_FINDER_RNG_SHA1_H

#include "rng/seed.h"
#include "utils/types.h"

#define SHA1_BUFFER_LEN 80
#define SHA1_ALPHA_LEN  5

typedef struct sha1_t {
	u32 data[SHA1_BUFFER_LEN];
	u32 alpha[SHA1_ALPHA_LEN];
} sha1_t;

u64 sha1_hash(sha1_t *ctx);

struct sha1_t sha1_init(struct seed_ctx_t *ctx);

void sha1_set_date(struct sha1_t *ctx, seed_t *seed);

void sha1_set_time(struct sha1_t *ctx, seed_t *seed);

void sha1_set_timer0(struct sha1_t *ctx, seed_t *seed);

void sha1_set_keypress(struct sha1_t *ctx, seed_t *seed);

#endif /* SEED_FINDER_RNG_SHA1_H */
