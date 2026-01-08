#include "rng/seed.h"

#include <stdio.h>
#include <stdlib.h>

#include "config/parameters.h"
#include "locale/nazos.h"

void seed_ctx_init(struct seed_ctx_t *ctx, struct parameters_t *params)
{
	if (ctx == NULL || params == NULL) {
		return;
	}

	ctx->mac_address = params->mac_address;

	// todo
}
