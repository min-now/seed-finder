#include "search.h"

#include <stdlib.h>

#include "locale/keypresses.h"
#include "locale/params.h"
#include "rng/seed.h"
#include "rng/sha1.h"
#include "utils/types.h"

const u8 NO_WEATHER_DATES[12][31] = {
	{ 1, 2, 0, 0, 0, 6, 7, 8, 9, 10,  0,  0,  0, 14, 15, 16, 17, 18, 19,  0,  0, 22, 23, 24, 25, 26,  0,  0,  0, 30, 31 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{ 1, 2, 3, 0, 0, 6, 7, 8, 9, 10, 11,  0,  0, 14, 15, 16, 17, 18, 19,  0,  0, 22, 23, 24, 25, 26,  0,  0,  0, 30, 31 },
	{ 0, 0, 0, 0, 0, 6, 7, 8, 0,  0,  0, 12,  0,  0, 15, 16, 17,  0,  0,  0,  0,  0, 23, 24,  0, 26, 27,  0, 29,  0,  0 },
	{ 1, 2, 0, 0, 0, 6, 7, 8, 9, 10,  0,  0,  0, 14, 15, 16, 17, 18, 19,  0,  0, 22, 23, 24, 25, 26,  0,  0,  0, 30, 31 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{ 1, 2, 3, 0, 0, 6, 7, 8, 9, 10, 11,  0,  0, 14, 15, 16, 17, 18, 19,  0,  0, 22, 23, 24, 25, 26,  0,  0,  0, 30, 31 },
	{ 0, 0, 0, 0, 0, 6, 0, 8, 0,  0,  0,  0, 12, 13,  0, 15, 16, 17,  0,  0, 20,  0,  0, 23, 24,  0, 26, 27,  0, 29,  0 },
	{ 1, 2, 0, 0, 0, 6, 7, 8, 9, 10,  0,  0,  0, 14, 15, 16, 17, 18, 19,  0,  0, 22, 23, 24, 25, 26,  0,  0,  0, 30,  0 },
	{ 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0 },
	{ 1, 2, 3, 0, 0, 6, 7, 8, 9, 10, 11,  0,  0, 14, 15, 16, 17, 18, 19,  0,  0, 22, 23, 24, 25, 26,  0,  0, 30,  0,  0 },
	{ 0, 0, 0, 4, 0, 6, 7, 0, 0, 10,  0, 12, 13,  0, 15, 16, 17,  0, 19, 20,  0,  0, 23, 24,  0, 26, 27,  0, 29,  0,  0 },
};

void search(params_t *params, seed_t *out, size_t out_size, bool (*callback)(u64 seed, seed_t *ctx))
{
	sha1_t ctx = sha1_init(params);

	for (u32 kp_idx = 0; kp_idx < KEYPRESS_AMT; ++kp_idx) {
		if (params->max_keypresses < KEYPRESSES[kp_idx].button_amt) {
			continue;
		}
		for (u32 vcount = params->min_vcount; vcount <= params->max_vcount; ++vcount) {
			for (u32 vframe = params->min_vframe; vframe <= params->max_vframe; ++vframe) {
				for (u32 gxstat = params->min_gxstat; gxstat <= params->max_gxstat; ++gxstat) {
					for (u32 timer0 = params->min_timer0; timer0 <= params->max_timer0; ++timer0) {
						sha1_set_timer0(&ctx, timer0, vcount);
						for (u16 year = params->min_year; year <= params->max_year; ++year) {
							for (u8 month = params->min_month; month <= params->max_month; ++month) {
								for (u8 day = params->min_day; day <= params->max_day; ++day) {
									if (params->skip_weather_dates && !NO_WEATHER_DATES[month - 1][day - 1]) {
										continue;
									}

									sha1_set_date(&ctx, year, month, day);

									for (u8 hour = params->min_hour; hour <= params->max_hour; ++hour) {
										for (u8 minute = params->min_minute; minute <= params->max_minute; ++minute) {
											for (u8 second = params->min_second; second <= params->max_second;
												 ++second) {
												sha1_set_time(&ctx, hour, minute, second);

												u64 seed = sha1_hash(&ctx);
												callback(seed, NULL);
												// hash seed, then callback
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
