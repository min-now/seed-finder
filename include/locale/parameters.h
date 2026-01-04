#ifndef SEED_FINDER_LOCALE_PARAMETERS_H
#define SEED_FINDER_LOCALE_PARAMETERS_H

#include "locale/language.h"
#include "utils/types.h"

struct parameters_t

{

	u64 mac_address;

	u32 min_timer0, max_timer0;

	u8 min_vcount, max_vcount;

	u8 min_gxstat, max_gxstat;

	u8 min_vframe, max_vframe;

	enum language_e language;

	enum game_version_e game_version;

	u8 min_hour, max_hour;

	u8 min_minute, max_minute;

	u8 min_second, max_second;

	u16 min_year, max_year;

	u8 min_month, max_month;

	u8 min_day, max_day;
};

void parameters_set_default(struct parameters_t *params, enum game_version_e);

#endif /* SEED_FINDER_LOCALE_PARAMETERS */
