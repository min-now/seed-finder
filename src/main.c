#include <stdio.h>
#include <string.h>

#include "config/parameters.h"
#include "locale/nazos.h"
#include "rng/mtrng.h"
#include "rng/rng.h"
#include "rng/seed.h"
#include "rng/sha1.h"
#include "utils/macros.h"

static void test_params(void)
{
	struct parameters_t params;
	parameters_set_default(&params, GAME_NOT_SET);

	params.min_year = 2000;
	params.max_year = 2000;

	params.max_keypresses = 0;

	parameters_validate(&params);
}

static void test_mtrng(void)
{
	mtrng_t mtrng;
	mtrng_init(&mtrng, 0x1B25D82B);

	u8 ivs[6] = { 0 };
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
		// printf("%X has pkrs on frame: %zu\n", mtrng.current(&mtrng),
		// mtrng.frame);
	}
}

void test_sha1(void)
{
	struct seed_ctx_t seed = {
		.mac_address = 0x9BFF04BEE,
		.timer0      = 0x10F4,
		.gxstat      = 0x6,
		.vframe      = 0x8,
		.vcount      = 0x82,

		.day      = 9,
		.month    = 5,
		.year     = 2080,
		.keypress = 0x7D2F0000,

		.hour   = 22,
		.minute = 58,
		.second = 5,

		.soft_reset = false,
		.nazos      = &NAZOS[LANG_ENG][GAME_WHITE_2],
	};

	printf("nazos:\n");
	for (u8 i = 0; i < 5; ++i) {
		printf("%w32X ", (*seed.nazos)[i]);
	}

	printf("\nnazos new:\n");
	for (u8 i = 0; i < 5; ++i) {
		printf("%w32X ", NAZOS[LANG_ENG][GAME_WHITE_2][i]);
	}

	printf("\n\n");


	sha1_t sha1 = sha1_init(&seed);

	sha1_set_timer0(&sha1, &seed);
	sha1_set_date(&sha1, &seed);
	sha1_set_time(&sha1, &seed);
	sha1_set_keypress(&sha1, &seed);

	u64 res = sha1_hash(&sha1);

	rng_t test_rng = rng_init(res, GAME_NOT_SET);
	//	test_rng.next(&test_rng);
	printf("%w64X: %w64X\n", res, test_rng.next(&test_rng));
}

int main(void)
{
	test_sha1();
	test_params();
	test_mtrng();

	for (size_t i = 0; i < 5; ++i) {
		printf("%x ", NAZOS[LANG_ENG][GAME_WHITE_2][i]);
	}

	puts("");

	rng_t rng = rng_init(0x30, GAME_WHITE_2);

	rng.adv(&rng, 4);
	rng.init_adv(&rng);

	printf("%lX\n", rng.rng);

	return 0;
}
