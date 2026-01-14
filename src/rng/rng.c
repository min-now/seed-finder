#include "rng/rng.h"

#include "locale/version.h"
#include "utils/types.h"

static void rng_init_adv_helper(rng_t *rng, u8 rounds);

rng_t rng_init(u64 seed, version_t version)
{
	return (rng_t) {
		.seed  = seed,
		.rng   = seed,
		.frame = 0,

		.reset = &rng_reset,
		.rand  = &rng_rand,

		.adv      = &rng_adv,
		.adv_rand = &rng_adv_rand,

		.next      = &rng_next,
		.next_rand = &rng_next_rand,

		.peek      = &rng_peek,
		.peek_rand = &rng_peek_rand,

		.init_adv = (version == VERSION_BLACK || version == VERSION_WHITE) ? &rng_init_adv_bw1 : &rng_init_adv_bw2,

	};
}

void rng_reset(rng_t *rng)
{
	rng->rng = rng->seed;

	rng->frame = 0;
}

void rng_reseed(rng_t *rng, u64 seed)
{
	rng->rng = rng->seed = seed;

	rng->frame = 0;
}

u64 rng_rand(const rng_t *rng, u32 x)
{
	return ((rng->rng >> 32) * x) >> 32;
}

u64 rng_adv(rng_t *rng, size_t n)
{
	for (size_t i = 0; i < n; ++i) {
		rng->rng = (rng->rng * 0x5D588B656C078965) + 0x269EC3;
	}

	rng->frame += n;

	return rng->rng;
}

u64 rng_adv_rand(rng_t *rng, size_t n, u32 x)
{
	rng->adv(rng, n);
	return rng->rand(rng, x);
}

u64 rng_next(rng_t *rng)
{
	return rng->adv(rng, 1);
}

u64 rng_next_rand(rng_t *rng, u32 x)
{
	rng->next(rng);
	return rng->rand(rng, x);
}

u64 rng_peek(const rng_t *rng, size_t n)
{
	u64 temp = rng->rng;
	for (size_t i = 0; i < n; ++i) {
		temp = (temp * 0x5D588B656C078965) + 0x269EC3;
	}

	return temp;
}

u64 rng_peek_rand(const rng_t *rng, size_t n, u32 x)
{
	return ((rng->peek(rng, n) >> 32) * x) >> 32;
}

u64 rng_init_adv_bw1(rng_t *rng)
{
	rng_init_adv_helper(rng, 5);

	return rng->rng;
}

u64 rng_init_adv_bw2(rng_t *rng)
{
	rng_init_adv_helper(rng, 1);

	rng->adv(rng, 3);

	rng_init_adv_helper(rng, 4);

	for (u8 i = 0; i < 100; ++i) {
		const u64 temp[3] = {
			rng->next_rand(rng, 15),
			rng->next_rand(rng, 15),
			rng->next_rand(rng, 15),
		};

		if (temp[0] != temp[1] && temp[0] != temp[2] && temp[2] != temp[1]) {
			break;
		}
	}

	return rng->rng;
}

static void rng_init_adv_helper(rng_t *rng, u8 rounds)
{
	static const u8 RNG_ADVANCEMENT_TABLE[5][4] = {
		{ 50, 100, 100, 100 },
        { 50,  50, 100, 100 },
        { 30,  50, 100, 100 },
        { 25,  30,  50, 100 },
        { 20,  25,  33,  50 }
	};

	for (u8 round = 0; round < rounds; ++round) {
		for (u8 i = 0; i < 5; ++i) {
			for (u8 j = 0; j < 4; ++j) {
				if (RNG_ADVANCEMENT_TABLE[i][j] == 100) {
					break;
				}

				if (rng->next_rand(rng, 101) <= RNG_ADVANCEMENT_TABLE[i][j]) {
					break;
				}
			}
		}
	}
}
