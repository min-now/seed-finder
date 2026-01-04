#include "locale/parameters.h"
#include "rng/rng.h"

#include <stdio.h>

static void test_params(void)
{
	struct parameters_t params;
	parameters_set_default(&params, GAME_NOT_SET);

	params.min_year = 2000;
	params.max_year = 2000;
	//	params.max_month = 1;

	parameters_validate(&params);
}

int main(void)
{

	test_params();

	struct rng_t rng = rng_init(0x30, GAME_WHITE_2);

	rng.adv(&rng, 4);

	printf("%lX\n", rng.rng);

	return 0;
}
