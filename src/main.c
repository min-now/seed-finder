#include "rng/rng.h"

#include <stdio.h>

int main(void)
{
	struct rng_t rng = rng_init(0x30, GAME_WHITE_2);

	rng.adv(&rng, 4);

	printf("%lX", rng.rng);

	return 0;
}
