#include "rng/sha1.h"

#include "rng/seed.h"
#include "utils/macros.h"

#include <string.h>

#define SECTION_1(X, Y, A, B, C, D, E, I)                          \
	X = ROT_L(A, 5) + ((B & C) | ((~B) & D)) + E + 0x5A827999 + I; \
	Y = ROT_R(B, 2);

#define CALC_W(DATA, IDX)                                                    \
	DATA[IDX] = ROT_L(                                                       \
		DATA[IDX - 3] ^ DATA[IDX - 8] ^ DATA[IDX - 14] ^ DATA[IDX - 16], 1);

#define CALC_W_SIMD(DATA, IDX)                                                \
	DATA[IDX] = ROT_L(                                                        \
		DATA[IDX - 6] ^ DATA[IDX - 16] ^ DATA[IDX - 28] ^ DATA[IDX - 32], 2);

u64 sha1_hash(struct sha1_t *ctx)
{
	u32 *alpha = ctx->alpha;
	u32 *data  = ctx->data;

	u32 a = alpha[0], b = alpha[1], c = alpha[2], d = alpha[3], e = alpha[4],
		t = 0;

	// clang-format off
	CALC_W(data, 17); CALC_W(data, 20); CALC_W(data, 23); CALC_W(data, 25); 
	CALC_W(data, 26); CALC_W(data, 28); CALC_W(data, 29); CALC_W(data, 31); 

	for (size_t i = 32; i < 80; ++i) {
		CALC_W_SIMD(data, i);
	}

	u32 f, k, temp;
	for (size_t i = 9; i < 80; ++i) {
		if (i < 20) {
			f = (b & c) | ((~b) & d);
			k = 0x5A827999;
		}

		temp = ROT_L(a, 5) + f + e + k + data[i];
		e = d;
		d = c;
		c = ROT_L(b, 30);
		b = a;
		a = temp;
	}

	SECTION_1(t, b, a, b, c, d, e, data[9]);
	SECTION_1(a, e, t, a, b, c, d, data[10]);
	// clang-format on
}

void sha1_set_date(struct sha1_t *ctx, u16 year, u8 month, u8 day)
{
	u16 y = year, m = month, d = day;

	// https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Keith
	u8 dayofweek = (d += m < 3 ? y-- : y - 2,
					23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) %
				   7;

	ctx->data[8] =
		BCD[year - 2000] << 24 | BCD[month] << 16 | BCD[day] << 8 | dayofweek;
}

void sha1_set_time(struct sha1_t *ctx, u8 hour, u8 minute, u8 second)
{
	u8 x         = hour >= 12 ? 0x40 : 0;
	ctx->data[9] = BCD[hour + x] << 24 | BCD[minute] << 16 | BCD[second] << 8;
}

void sha1_set_timer0(struct sha1_t *ctx, u32 timer0, u32 vcount)
{
	ctx->data[5] = CHANGE_ENDIAN((vcount << 16) | timer0);
}

void sha1_set_keypress(struct sha1_t *ctx, u32 keypress)
{
	ctx->data[12] = keypress;
}

struct sha1_t sha1_init(struct seed_ctx_t *seed)
{
	// Pass in pointer instead?

	struct sha1_t sha1;

	memset(sha1.data, 0, SHA1_BUFFER_LEN * sizeof(sha1.data[0]));

	memcpy(sha1.data, seed->nazos, 5 * sizeof(sha1.data[0]));

	sha1.data[5] = CHANGE_ENDIAN((seed->vcount << 16) | seed->timer0);
	sha1.data[6] = seed->mac_address & 0xFFFF;

	if (seed->soft_reset) {
		sha1.data[6] ^= 0x1000000;
	}

	sha1.data[7] =
		(seed->mac_address >> 16) ^ (seed->vframe << 24) ^ seed->gxstat;

	sha1.data[13] = 0x80000000;
	sha1.data[10] = sha1.data[11] = sha1.data[14] = 0;
	sha1.data[15]                                 = 0x1A0;

	sha1.data[18] =
		ROT_L(sha1.data[15] ^ sha1.data[10] ^ sha1.data[4] ^ sha1.data[2], 1);

	memset(sha1.alpha, 0, SHA1_ALPHA_LEN * sizeof(sha1.alpha[0]));

	return sha1;
}
