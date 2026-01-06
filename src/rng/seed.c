#include "rng/seed.h"

#include "config/parameters.h"
#include "locale/nazos.h"

#include <stdio.h>
#include <stdlib.h>

void seed_ctx_init(struct seed_ctx_t *ctx, struct parameters_t *params)
{
	if (ctx == NULL || params == NULL) {
		return;
	}

	ctx->mac_address = params->mac_address;

	// implement other languages/versions
	switch (params->game_version) {
	case GAME_WHITE_2:
		ctx->nazos = &W2_ENG_NAZOS;
		break;

	default:
		printf("nazos unimplemented\n");
		break;
	}
}
