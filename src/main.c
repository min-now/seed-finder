#include <stdio.h>
#include <string.h>

#include "locale/nazos.h"
#include "locale/params.h"
#include "rng/mtrng.h"
#include "rng/rng.h"
#include "rng/seed.h"
#include "rng/sha1.h"
#include "utils/macros.h"

#include "engine/trainer.h"

#include "search.h"

[[maybe_unused]]
static void test_params(void)
{
	params_t params;
	params_set_default(&params, VERSION_NONE);

	params.min_year = 2000;
	params.max_year = 2000;

	params.max_keypresses = 0;

	params_validate(&params);
}

[[maybe_unused]]
static void test_mtrng(void)
{
	mtrng_t mtrng;
	mtrng_init(&mtrng, 0x1B25D82B);

	u8 ivs[6] = { 0 };
	/*
	mtrng.get_ivs(&mtrng, &ivs);
	for (size_t j = 0; j < 6; ++j) {
		printf("%d ", ivs[j]);
	}
	*/


	size_t frame = 0;
	for (u32 i = 0; i < 0xFFFFFFFF; ++i) {
		mtrng_reset(&mtrng, i);

//		mtrng_get_ivs(&mtrng, &ivs);
		// 30+/31/30+/6+/30+/31

//		if (ivs[0] < 29 || ivs[1] != 31 || ivs[2] < 30 || ivs[4] < 30 || ivs[5] != 31) {
//			continue;
//		}
//

		frame = 4800;
		int pkrs_count = 0;
		for (mtrng_advance(&mtrng, frame); frame < 5200; frame++) {
			if (mtrng_has_pkrs(&mtrng)) {
				mtrng_next(&mtrng); frame++;
				if (mtrng_has_pkrs(&mtrng)) {
					mtrng_next(&mtrng); frame++;
					if (mtrng_has_pkrs(&mtrng)) {
						printf("b3b pokerus frame! seed: %x, frame: %d\n", i, frame); 
					}
				}
			} else {
				mtrng_next(&mtrng);
			}
		}
	}
}

[[maybe_unused]]
void test_sha1(void)
{
	seed_t seed = {
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
		.nazos      = &NAZOS[LANG_ENG][VERSION_WHITE_2],
	};

	printf("nazos:\n");
	for (u8 i = 0; i < 5; ++i) {
		printf("%w32X ", (*seed.nazos)[i]);
	}

	printf("\nnazos new:\n");
	for (u8 i = 0; i < 5; ++i) {
		printf("%w32X ", NAZOS[LANG_ENG][VERSION_WHITE_2][i]);
	}

	printf("\n\n");

	params_t params;
	params_set_default(&params, VERSION_WHITE_2);

	params.language    = LANG_ENG;
	params.mac_address = seed.mac_address;

	printf("%x %x \n", params.min_vcount, params.min_gxstat);

	sha1_t sha1 = sha1_init(&params);

	sha1_set_timer0(&sha1, seed.timer0, seed.vcount);
	sha1_set_date(&sha1, seed.year, seed.month, seed.day);
	sha1_set_time(&sha1, seed.hour, seed.minute, seed.second);
	sha1_set_keypress(&sha1, seed.keypress);

	u64 res = sha1_hash(&sha1);

	rng_t test_rng = rng_init(res, VERSION_NONE);
	//	test_rng.next(&test_rng);
	printf("%w64X: %w64X\n", res, test_rng.next(&test_rng));
}

bool iv_callback(u64 seed, params_t *params)
{
	mtrng_t mtrng;
	mtrng_init(&mtrng, HIGH_32(seed));

	u8 ivs[6] = { 0 };
	mtrng_get_ivs(&mtrng, &ivs);
	for (size_t j = 0; j < 6; ++j) {
		if (ivs[j] < 26) {
			return false;
		}
	}

	return true;
}

static void test_spinners(void)
{
	struct trainer_t dummy_npc = {.timer = 6, .delay = 2, .dirs_amt = 4, .type = TRAINER_TYPE_SPINNER_DEAF, .dirs = {DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT}, .status = TRAINER_STATUS_ACTIVE};
	rng_t rng = rng_init(0x86B4A18F217653E9, VERSION_WHITE_2);

	trainer_init(&dummy_npc);

	trainer_load(&dummy_npc, &rng);
	trainer_activate(&dummy_npc);
	

	for (size_t i = 0; i < 130; ++i) {
		trainer_advance(&dummy_npc, &rng);
		trainer_print(&dummy_npc);
	}

}


bool metronome_callback(u64 seed, params_t *ctx)
{
	const u16 DRILBUR_CATCH_VALUE = 45643;
	rng_t rng = rng_init(seed, VERSION_WHITE_2);

	for (size_t i = 0; i < 3; ++i) {
		rng_next(&rng);
		if (rng.rng >> 48 >= DRILBUR_CATCH_VALUE) {
			return false;
		}
	}
	return true;

	/*
	if (rng_peek_rand(&rng, 1, 554) == 169) {
		if (rng_peek_rand(&rng, 2, 100) < 80) {
			if (rng_peek_rand(&rng, 3, 8) == 1) {
				if (rng_peek_rand(&rng, 4, 16) == 0) {
					if (rng_peek_rand(&rng, 6, 16) != 0) {
						if (rng_peek_rand(&rng, 12, 554) == 286) {
						   //	&& rng_peek_rand(&rng, 14, 554) == 293) {
							return true;
						}
					}
				}
			}
		}
	}
	*/
   /*	else if (rng_peek_rand(&rng, 1, 552) == 324) {
		if (rng_peek_rand(&rng, 2, 16) == 0) {
			printf("shadow punch crit || ");
			return true;
		}
	} */
	return false;

}


int main([[maybe_unused]] int argc, [[maybe_unused]] const char *argv[])
{
//	parser_load_file("doesntexist.txt", INI_TYPE_PROFILE, NULL);

	//rng_t rng = rng_init(0x30, VERSION_WHITE_2);

	//rng.init_adv(&rng);
	//rng.adv(&rng, 808);
	//rng.print(&rng);


	params_t params = params_load("tts.ini");
	params_validate(&params);
	search(&params, metronome_callback);

	//test_spinners();
	/*
	test_params();


		*/

	return 0;
}
