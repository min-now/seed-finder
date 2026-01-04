#include "rng/sha1.h"

#include "rng/seed.h"
#include "utils/macros.h"

#include <string.h>

struct sha1_t sha1_init(struct seed_ctx_t *seed)
{
	// Pass in pointer instead?
	struct sha1_t ctx;

	memset(ctx.data, 0, SHA1_BUFFER_SIZE * sizeof(ctx.data[0]));

	memcpy(ctx.data, seed->nazos, 5 * sizeof(ctx.data[0]));

	ctx.data[5] = CHANGE_ENDIAN((seed->vcount << 16) | seed->timer0);
	ctx.data[6] = seed->mac_address & 0xFFFF;

	if (seed->soft_reset) {
		ctx.data[6] ^= 0x1000000;
	}

	ctx.data[7] =
		(seed->mac_address >> 16) ^ (seed->vframe << 24) ^ seed->gxstat;

	return ctx;
}
