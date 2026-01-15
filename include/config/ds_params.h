#ifndef SEED_FINDER_CONFIG_DS_PARAMS_H
#define SEED_FINDER_CONFIG_DS_PARAMS_H

#include "utils/types.h"

typedef struct ds_params_s {
	u32 min_timer0, max_timer0;

	u32 min_vcount, max_vcount;
	u32 min_vframe, max_vframe;
	u32 min_gxstat, max_gxstat;

	u16 min_year, max_year;
	u8  min_month, max_month;
	u8  min_day, max_day;

	u8 min_hour, max_hour;
	u8 min_minute, max_minute;
	u8 min_second, max_second;

} ds_params_t;

#endif /* SEED_FINDER_CONFIG_DS_PARAMS_H */
