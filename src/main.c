#include <stdio.h>

#include "rng/rng.h"

int main(void)
{
	struct rng_t rng = rng_init(0x30, GAME_WHITE_2);

	rng.adv(&rng, 4);

	printf("%llx", rng.rng);

	return 0;
}
