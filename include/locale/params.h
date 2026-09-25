#ifndef SEED_FINDER_LOCALE_PARAMS_H
#define SEED_FINDER_LOCALE_PARAMS_H

#include "inih/ini.h"

#include "locale/language.h"
#include "locale/version.h"
#include "utils/types.h"

typedef enum search_type_e: u32 {
	SEARCH_TYPE_IV = 0,
	SEARCH_TYPE_IV_POKERUS,
	SEARCH_TYPE_TRAINER_SKIP,
	SEARCH_TYPE_PLASMA_SKIP,
	SEARCH_TYPE_METRONOME,

	SEARCH_TYPE_AMT,
} search_type_t;

typedef union iv_u {
	struct [[gnu::packed]] {
		u8 hp, atk, def, spatk, spdef, speed;
	};
	u8 ivs[6];
} iv_t;

typedef struct params_s {
	u64 mac_address;

	u8 max_keypresses;

	iv_t ivs;
	size_t min_pokerus, max_pokerus;

  bool skip_weather_dates;
  bool soft_reset;

  search_type_t search_type;
  
  bool search_all_params;

  u32 min_timer0, max_timer0;
  u32 min_vcount, max_vcount;
  u32 min_gxstat, max_gxstat;
  u32 min_vframe, max_vframe;

  u8 min_hour, max_hour;
  u8 min_minute, max_minute;
  u8 min_second, max_second;
  u16 min_year, max_year;
  u8 min_month, max_month;
  u8 min_day, max_day;

  language_t language;

  version_t version;

  //	const u32 (*nazos)[5];
} params_t;

// void params_search(params_t *params, seed_t *output, bool (*callback)(seed_t *));
//

params_t params_load(const char *path);

void params_set_default(params_t *params, version_t version);

void params_validate(params_t *params);

void params_print(FILE *stream, params_t *params);

#endif /* SEED_FINDER_LOCALE_PARAMS_H */
