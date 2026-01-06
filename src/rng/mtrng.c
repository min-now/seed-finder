#include <string.h>

#include "rng/mtrng.h"

#include "utils/macros.h"

void mtrng_init(mtrng_t *mtrng, u32 seed)
{
#ifdef DEBUG
	if (mtrng == NULL) {
		PRINT_ERROR_ABORT("mtrng_t *mtrng is NULL");
	}
#endif

	init_table(mtrng, seed);
	
	mtrng->shuffle 	= &mtrng_shuffle;
	mtrng->advance 	= &mtrng_advance;
	mtrng->reset 	= &mtrng_reset;
	mtrng->next 	= &mtrng_next;
	mtrng->current 	= &mtrng_current;

	mtrng->has_pkrs = &mtrng_has_pkrs;
	mtrng->get_ivs 	= &mtrng_get_ivs;
}

void mtrng_reset(mtrng_t *mtrng, u32 seed)
{
	init_table(mtrng, seed);
}

void mtrng_advance(mtrng_t *mtrng, size_t n)
{
#ifdef DEBUG
	if (n == 0) {
		PRINT_ERROR("cannot advance mtrng by 0 frames");
		return;
	}
#endif

	n += mtrng->index;
	while (n >= MTRNG_TABLE_SIZE) {
		mtrng->shuffle(mtrng);
		n -= MTRNG_TABLE_SIZE;
	}
	
	mtrng->frame++;
	mtrng->index = n;
}

u32 mtrng_next(mtrng_t *mtrng)
{
	mtrng->index++;
	mtrng->frame++;

	if (mtrng->index >= MTRNG_TABLE_SIZE) {
		mtrng->shuffle(mtrng);
	}


	return mtrng->current(mtrng);
}

u32 mtrng_current(mtrng_t *mtrng)
{
	u32 y = mtrng->table[mtrng->index];

	y ^= y >> 11;
	y ^= y << 7 & 0x9D2C5680;
	y ^= y << 15 & 0xEFC60000;
	y ^= y >> 18;

	return y & 0xFFFFFFFF;
}


void mtrng_shuffle(mtrng_t *mtrng)
{
	for (size_t i = 0; i < 624; ++i) {
		u32 y = (mtrng->table[i] & 0x80000000)
				| (mtrng->table[(i + 1) % MTRNG_TABLE_SIZE] & 0x7FFFFFFF);

		y &= 0xFFFFFFFF;

		u32 y1 = y >> 1;
		if (y % 2 != 0) {
			y1 ^= 0x9908B0DF;
		}

		mtrng->table[i] = mtrng->table[(i + 397) % MTRNG_TABLE_SIZE] ^ y1;
	}
	mtrng->index = 0;
}


void mtrng_get_ivs(mtrng_t *mtrng, u8 (*restrict ivs)[6]) 
{
	for (size_t i = 0; i < 6; ++i) {
		(*ivs)[i] = mtrng->next(mtrng) >> 27;
	}
}

bool mtrng_has_pkrs(mtrng_t *mtrng)
{
	u16 val = mtrng->current(mtrng) >> 16;
	return val == 0x4000 || val == 0x8000 || val == 0xC000;
}





