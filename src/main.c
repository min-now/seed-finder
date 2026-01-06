
#include "config/parameters.h"
#include "locale/nazos.h"
#include "rng/rng.h"
#include "rng/sha1.h"
#include "utils/macros.h"

#include "rng/mtrng.h"

#include <stdio.h>
#include <string.h>

static void test_params(void)
{
	struct parameters_t params;
	parameters_set_default(&params, GAME_NOT_SET);

	params.min_year       = 2000;
	params.max_year       = 2000;
	params.max_keypresses = 0;

	parameters_validate(&params);
}

static void test_mtrng(void) 
{
	mtrng_t mtrng;
	mtrng_init(&mtrng, 0x1B25D82B);

	u8 ivs[6] = {0};
	mtrng.get_ivs(&mtrng, &ivs);
	for (size_t j = 0; j < 6; ++j) {
		printf("%d ", ivs[j]);
	}

	return;

	for (u32 i = 3; i < 400'000'000; ++i) {
		mtrng_reset(&mtrng, i);

		mtrng.get_ivs(&mtrng, &ivs);

		if (ivs[0] != 31 || ivs[1] != 31 || ivs[2] < 30 || ivs[3] < 30 || ivs[4] != 31) {
			continue;
		}

		for (size_t j = 0; j < 6; ++j) {
			printf("%d ", ivs[j]);
		}

		while (!mtrng.has_pkrs(&mtrng) && mtrng.frame <= MTRNG_TABLE_SIZE * 2) {
			mtrng.next(&mtrng);
		}

		printf("\n i: %u\n", i);
		//printf("%X has pkrs on frame: %zu\n", mtrng.current(&mtrng), mtrng.frame);
	}
}

int main(void)
{
	test_params();
	test_mtrng();

	for (size_t i = 0; i < 5; ++i) {
		printf("%x ", NAZOS[LANG_ENG][GAME_WHITE_2][i]);
	}

	struct rng_t rng = rng_init(0x30, GAME_WHITE_2);

	rng.adv(&rng, 4);

	printf("%lX\n", rng.rng);

	return 0;
}
