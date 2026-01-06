#ifndef SEED_FINDER_RNG_SHA1_H
#define SEED_FINDER_RNG_SHA1_H

#include "rng/seed.h"
#include "utils/types.h"

#define SHA1_BUFFER_LEN 80
#define SHA1_ALPHA_LEN  5

static const u8 BCD[] = { 0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   16,  17,  18,  19,  20,  21,  22,
						  23,  24,  25,  32,  33,  34,  35,  36,  37,  38,  39,  40,  41,  48,  49,  50,  51,
						  52,  53,  54,  55,  56,  57,  64,  65,  66,  67,  68,  69,  70,  71,  72,  73,  80,
						  81,  82,  83,  84,  85,  86,  87,  88,  89,  96,  97,  98,  99,  100, 101, 102, 103,
						  104, 105, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 128, 129, 130, 131, 132,
						  133, 134, 135, 136, 137, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153 };

struct sha1_t {
	u32 data[SHA1_BUFFER_LEN];
	u32 alpha[SHA1_ALPHA_LEN];
};

struct sha1_t sha1_init(struct seed_ctx_t *ctx);

void sha1_set_date(struct sha1_t *ctx, u16 year, u8 month, u8 day);

void sha1_set_time(struct sha1_t *ctx, u8 hour, u8 minute, u8 second);

void sha1_set_timer0(struct sha1_t *ctx, u32 timer0, u32 vcount);

void sha1_set_keypress(struct sha1_t *ctx, u32 keypress);

#endif /* SEED_FINDER_RNG_SHA1_H */
