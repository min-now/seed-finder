#include "rng/sha1.h"

#include <string.h>

#include "locale/nazos.h"
#include "rng/rng.h"
#include "rng/seed.h"
#include "utils/macros.h"

#define SECTION_1(X, Y, A, B, C, D, E, I)                          \
	X = ROT_L(A, 5) + ((B & C) | ((~B) & D)) + E + 0x5A827999 + I; \
	Y = ROT_R(B, 2);

#define H0 0x67452301
#define H1 0xEFCDAB89
#define H2 0x98BADCFE
#define H3 0x10325476
#define H4 0xC3D2E1F0

#define CALC_W(DATA, IDX) DATA[IDX] = ROT_L(DATA[IDX - 3] ^ DATA[IDX - 8] ^ DATA[IDX - 14] ^ DATA[IDX - 16], 1);

#define CALC_W_SIMD(DATA, IDX) DATA[IDX] = ROT_L(DATA[IDX - 6] ^ DATA[IDX - 16] ^ DATA[IDX - 28] ^ DATA[IDX - 32], 2);

static const u8 BCD[] = {
	0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   16,  17,  18,  19,  20,  21,  22,  23,  24,  25,
	32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  48,  49,  50,  51,  52,  53,  54,  55,  56,  57,
	64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  80,  81,  82,  83,  84,  85,  86,  87,  88,  89,
	96,  97,  98,  99,  100, 101, 102, 103, 104, 105, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121,
	128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153,
};

u64 sha1_hash(sha1_t *sha1)
{
	// printf("sha1 message\n\n");
	// for (size_t idx = 0; idx < 16; ++idx) {
	// 	printf("%x ", sha1->data[idx]);
	// }
	// printf("\n\n");

	u32 vals[5] = { H0, H1, H2, H3, H4 };

	u32 a = H0, b = H1, c = H2, d = H3, e = H4;
	u32 f, k, temp;

	{
		size_t w_idx;

		CALC_W(sha1->data, 16);
		CALC_W(sha1->data, 17);

		CALC_W(sha1->data, 18);

		for (w_idx = 19; w_idx < 32; ++w_idx) {
			CALC_W(sha1->data, w_idx);
		}

		for (; w_idx < 80; ++w_idx) {
			CALC_W_SIMD(sha1->data, w_idx);
		}
	}

	for (size_t i = 0; i < 80; ++i) {
		if (i <= 19) {
			f = (b & c) | ((~b) & d);
			k = 0x5A827999;
		} else if (i <= 39) {
			f = b ^ c ^ d;
			k = 0x6ED9EBA1;
		} else if (i <= 59) {
			f = (b & c) | (b & d) | (c & d);
			k = 0x8F1BBCDC;
		} else {
			f = b ^ c ^ d;
			k = 0xCA62C1D6;
		}

		temp = ROT_L(a, 5) + f + e + k + sha1->data[i];
		e    = d;
		d    = c;
		c    = ROT_L(b, 30);
		b    = a;
		a    = temp;
	}

	vals[0] += a;
	vals[1] += b;
	vals[2] += c;
	vals[3] += d;
	vals[4] += e;

	/*
	for (u8 i = 0; i < 5; ++i) {
		printf("%x ", vals[i]);
	}
	putchar('\n');
	*/

	u64 p1 = BSWAP(a + H0);
	u64 p2 = BSWAP(b + H1);

	return (p2 << 32) | p1;
}

void sha1_set_date(sha1_t *sha1, u16 year, u8 month, u8 day)
{
	u16 y = year, m = month, d = day;

	// https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Keith
	u8 dayofweek = (d += m < 3 ? y-- : y - 2, 23 * m / 9 + d + 4 + y / 4 - y / 100 + y / 400) % 7;

	sha1->data[8] = BCD[year - 2000] << 24 | BCD[month] << 16 | BCD[day] << 8 | dayofweek;
}

void sha1_set_time(sha1_t *sha1, u8 hour, u8 minute, u8 second)
{
	u8 x          = hour >= 12 ? 0x40 : 0;
	sha1->data[9] = (BCD[hour] + x) << 24 | BCD[minute] << 16 | BCD[second] << 8;
}

void sha1_set_timer0(sha1_t *sha1, u32 timer0, u32 vcount)
{
	sha1->data[5] = BSWAP((vcount << 16) | timer0);
}

void sha1_set_vframe(sha1_t *sha1, u64 mac_address, u64 gxstat, u32 vframe)
{
	sha1->data[7] = (mac_address >> 16) ^ (vframe << 24) ^ gxstat;
}

void sha1_set_keypress(sha1_t *sha1, u32 keypress)
{
	sha1->data[12] = keypress;
}

sha1_t sha1_init(params_t *params)
{
	sha1_t sha1 = {};

	// might not need this?
	memset(sha1.data, 0, SHA1_BUFFER_LEN * sizeof(u32));

	// message[:5] = nazos
	memcpy(sha1.data, NAZOS[params->language][params->version], 5 * sizeof(u32));

	sha1.data[6] = params->mac_address & 0xFFFF;
	if (params->soft_reset) {
		sha1.data[6] ^= 0x1000000;
	}

	// vcount and gxstat are static for initial seed generation
//	sha1.data[7] = (params->mac_address >> 16) ^ (params->min_vframe << 24) ^ params->gxstat;

	// memset covers this
	sha1.data[10] = sha1.data[11] = sha1.data[14] = 0;

	sha1.data[13] = 0x80000000;

	sha1.data[15] = 0x1A0;

	// can precompute this
	// sha1.data[18] = ROT_L(sha1.data[15] ^ sha1.data[10] ^ sha1.data[4] ^ sha1.data[2], 1);

	return sha1;
}

/*
struct sha1_t _sha1_init(struct seed_ctx_t *seed)
{
	struct sha1_t sha1;

	memset(sha1.data, 0, SHA1_BUFFER_LEN * sizeof(sha1.data[0]));

	memcpy(sha1.data, *seed->nazos, 5 * sizeof(sha1.data[0]));

	sha1.data[5] = BSWAP((seed->vcount << 16) | seed->timer0);
	sha1.data[6] = seed->mac_address & 0xFFFF;

	if (seed->soft_reset) {
		sha1.data[6] ^= 0x1000000;
	}

	sha1.data[7] = (seed->mac_address >> 16) ^ (seed->vframe << 24) ^ seed->gxstat;

	sha1.data[10] = sha1.data[11] = sha1.data[14] = 0;

	sha1.data[13]                                 = 0x80000000;

	sha1.data[15] = 0x1A0;

	sha1.data[18] = ROT_L(sha1.data[15] ^ sha1.data[10] ^ sha1.data[4] ^ sha1.data[2], 1);

//	memset(sha1.alpha, 0, SHA1_ALPHA_LEN * sizeof(sha1.alpha[0]));

	return sha1;
}
*/

#undef H0
#undef H1
#undef H2
#undef H3
#undef H4
