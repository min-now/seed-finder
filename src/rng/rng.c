#include "utils/types.h"

#include "locale/parameters.h"
#include "rng/rng.h"

struct rng_t rng_init(const u64 seed, const enum game_version_e version)
{
	return (struct rng_t){.seed = seed,
						  .rng = seed,
						  .frame = 0,

						  .adv = &rng_adv,
						  .next = &rng_next,

						  .rand = &rng_rand,

						  .rand_next = &rng_rand_next,

						  .init_adv =
							  (version == GAME_BLACK || version == GAME_WHITE)
								  ? &rng_init_adv_bw1
								  : &rng_init_adv_bw2,

						  .reset = &rng_reset

	};
}

u64 rng_adv(struct rng_t *rng, const u32 amt)
{
	for (u32 i = 0; i < amt; i++)
	{
		rng->rng = (rng->rng * 0x5D588B656C078965) + 0x269EC3;
	}

	rng->frame += amt;

	return rng->rng;
}

u64 rng_next(struct rng_t *rng)
{
	return rng->adv(rng, 1);
}

u64 rng_rand(const struct rng_t *rng, const u32 num)
{
	return ((rng->rng >> 32) * num) >> 32;
}

u64 rng_rand_next(struct rng_t *rng, const u32 num)
{
	return ((rng->next(rng) >> 32) * num) >> 32;
}

static void init_adv_helper(struct rng_t *rng, u8 rounds)
{
	for (u8 round = 0; round < rounds; round++)
	{
		for (u8 i = 0; i < 5; i++)
		{
			for (u8 j = 0; j < 4; j++)
			{
				if (RNG_ADVANCEMENT_TABLE[i][j] == 100)
				{
					break;
				}

				if (rng->rand_next(rng, 101) <= RNG_ADVANCEMENT_TABLE[i][j])
				{

					break;
				}
			}
		}
	}
}

u64 rng_init_adv_bw1(struct rng_t *rng)
{
	init_adv_helper(rng, 5);

	return rng->rng;
}

u64 rng_init_adv_bw2(struct rng_t *rng)
{
	init_adv_helper(rng, 1);

	rng->adv(rng, 3);

	init_adv_helper(rng, 4);

	for (u8 i = 0; i < 100; i++)
	{
		const u64 temp[3] = {rng->rand_next(rng, 15), rng->rand_next(rng, 15),
							 rng->rand_next(rng, 15)};

		if (temp[0] != temp[1] && temp[0] != temp[2] && temp[2] != temp[1])
		{
			break;
		}
	}

	return rng->rng;
}

void rng_reset(struct rng_t *rng)
{
	rng->rng = rng->seed;
	rng->frame = 0;
}
