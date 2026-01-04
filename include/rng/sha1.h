#ifndef SEED_FINDER_RNG_SHA1_H
#define SEED_FINDER_RNG_SHA1_H

#include "utils/types.h"
#include "rng/seed.h"

#define SHA1_BUFFER_SIZE 80

struct sha1_t {
	u32 data[SHA1_BUFFER_SIZE];
};

struct sha1_t sha1_init(struct seed_ctx_t *ctx);

#endif /* SEED_FINDER_RNG_SHA1_H */
