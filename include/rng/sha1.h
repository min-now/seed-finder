#ifndef SEED_FINDER_RNG_SHA1_H
#define SEED_FINDER_RNG_SHA1_H

#include "locale/params.h"
#include "utils/types.h"

#define SHA1_BUFFER_LEN 80

// #define SHA1_ALPHA_LEN  5

typedef struct sha1_s {
	u32 data[SHA1_BUFFER_LEN];
	//	u32 alpha[SHA1_ALPHA_LEN];
} sha1_t;

u64 sha1_hash(sha1_t *ctx);

sha1_t sha1_init(params_t *params);

void sha1_set_date(sha1_t *sha1, u16 year, u8 month, u8 day);

void sha1_set_time(sha1_t *sha1, u8 hour, u8 minute, u8 second);

void sha1_set_timer0(sha1_t *sha1, u32 timer0, u32 vcount);

void sha1_set_keypress(sha1_t *sha1, u32 keypress);

// struct sha1_t sha1_init(params_t *params);
//  only call this in the nested loop if
// void sha1_set_other_vars(sha1_t *ctx, u64 mac_address, u32 vframe, u32 gxstat);

#endif /* SEED_FINDER_RNG_SHA1_H */
