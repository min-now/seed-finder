#ifndef SEED_FINDER_RNG_MTRNG_H
#define SEED_FINDER_RNG_MTRNG_H

#include <stdlib.h>

#include "utils/types.h"

#define MTRNG_TABLE_SIZE 624

// should figure out how to keep struct fields aligned

// clang-format off

typedef struct mtrng_t {
	size_t index, frame;
	u32 table[MTRNG_TABLE_SIZE];

	void (*reset)		(struct mtrng_t *, u32 seed);

	void (*advance)		(struct mtrng_t *, size_t);
	u32 (*next)			(struct mtrng_t *);
	u32 (*current)		(struct mtrng_t *);

	void (*shuffle)		(struct mtrng_t *);

	void (*get_ivs)		(struct mtrng_t *, u8 (*restrict)[6]);
	bool (*has_pkrs)	(struct mtrng_t *);
} mtrng_t;

void mtrng_init(mtrng_t *mtrng, u32 seed);
void mtrng_reset(mtrng_t *mtrng, u32 seed);

void mtrng_advance(mtrng_t *mtrng, size_t n);
u32 mtrng_next(mtrng_t *mtrng);
u32 mtrng_current(mtrng_t *mtrng);

void mtrng_shuffle(mtrng_t *mtrng);

void mtrng_get_ivs(mtrng_t *mtrng, u8 (*restrict ivs)[6]);
bool mtrng_has_pkrs(mtrng_t *mtrng);

// clang-format on

static inline void init_table(mtrng_t *mtrng, u32 seed)
{
	mtrng->index = 623;
	mtrng->frame = 0;
	mtrng->table[0] = seed;

	for (size_t i = 1; i < MTRNG_TABLE_SIZE; ++i) {
		mtrng->table[i] = 0x6C078965 * (mtrng->table[i - 1] ^ mtrng->table[i - 1] >> 30);
		mtrng->table[i] += i;
		mtrng->table[i] &= 0xFFFFFFFF;
	}
}


#endif /* SEED_FINDER_RNG_MTRNG_H */
