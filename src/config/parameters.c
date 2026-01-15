/*
#include "parameters.h"

#include <stdlib.h>

#include "locale/language.h"
#include "utils/macros.h"

#define CHECK_VALID(P, X, Y)                         \
	if ((P) < (X) || ((P) > (Y))) {                  \
		PRINT_ERROR("invalid value: " #P ": %d", P); \
		exit(1);                                     \
	}

#define CHECK_VALID_RANGE(P1, P2)                                                  \
	if ((P1) > (P2)) {                                                             \
		PRINT_ERROR(#P1 " cannot be greater than " #P2 " (have %d > %d)", P1, P2); \
		exit(1);                                                                   \
	}

void parameters_validate(struct parameters_t *params)
{
	printf("Validating parameters...");

	CHECK_VALID(params->max_keypresses, 0, 8);
	CHECK_VALID_RANGE(params->min_timer0, params->max_timer0);
	CHECK_VALID_RANGE(params->min_vcount, params->max_vcount);
	CHECK_VALID_RANGE(params->min_vframe, params->max_vframe);
	CHECK_VALID_RANGE(params->min_gxstat, params->max_gxstat);

	// Y/M/D
	{
		CHECK_VALID(params->min_year, 2000, 2099);
		CHECK_VALID(params->max_year, 2000, 2099);
		CHECK_VALID_RANGE(params->min_year, params->max_year);

		CHECK_VALID(params->min_month, 1, 12);
		CHECK_VALID(params->max_month, 1, 12);
		CHECK_VALID_RANGE(params->min_month, params->max_month);

		// Assume the amount of days in a month is 31 
		CHECK_VALID(params->min_day, 1, 31);
		CHECK_VALID(params->max_day, 1, 31);
		CHECK_VALID_RANGE(params->min_day, params->max_day);
	}

	// H:M:S
	{
		CHECK_VALID(params->min_hour, 0, 23);
		CHECK_VALID(params->max_hour, 0, 23);
		CHECK_VALID_RANGE(params->min_hour, params->max_hour);

		CHECK_VALID(params->min_minute, 0, 59);
		CHECK_VALID(params->max_minute, 0, 59);
		CHECK_VALID_RANGE(params->min_minute, params->max_minute);

		CHECK_VALID(params->min_second, 0, 59);
		CHECK_VALID(params->max_second, 0, 59);
		CHECK_VALID_RANGE(params->min_second, params->max_second);
	}

	puts("done!");
}

void parameters_set_default(struct parameters_t *params, const enum game_version_e game_version)
{
	{
		params->min_hour = params->min_minute = params->min_second = 0;
		params->max_hour                                           = 23;

		params->max_minute = params->max_second = 59;

		params->min_month = 1;
		params->max_month = 12;

		params->min_day = 1;
		params->max_day = 31;

		params->min_year = 2000;
		params->max_year = 2099;
	}

	params->game_version = game_version == GAME_NOT_SET ? GAME_WHITE_2 : game_version;
	params->language     = LANG_ENG;

	params->min_gxstat = params->max_gxstat = 0x6;

	params->max_keypresses = 8;

	switch (params->game_version) {
	case GAME_BLACK:
	case GAME_WHITE:
		params->min_timer0 = 0xC79;
		params->max_timer0 = 0xC81;
		break;
	case GAME_WHITE_2:
	case GAME_BLACK_2:
		params->min_timer0 = 0x10F2;
		params->max_timer0 = 0x10F6;
		params->min_vcount = params->max_vcount = 0x82;
		params->min_vframe = params->max_vframe = 0x8;
		break;
	default: break;
	}
}

*/
