#include <stdlib.h>
#include <string.h>

#include "inih/ini.h"

#include "locale/keypresses.h"
#include "locale/nazos.h"
#include "locale/language.h"
#include "locale/params.h"
#include "locale/version.h"
#include "utils/macros.h"
//#include "search.h"

#define CHECK_VALID(P, X, Y)                                                                                                                                                                           \
  if ((P) < (X) || ((P) > (Y))) {                                                                                                                                                                      \
    PRINT_ERROR("invalid value: " #P ": %d", P);                                                                                                                                                       \
    exit(1);                                                                                                                                                                                           \
  }

#define CHECK_VALID_RANGE(P1, P2)                                                                                                                                                                      \
  if ((P1) > (P2)) {                                                                                                                                                                                   \
    PRINT_ERROR(#P1 " cannot be greater than " #P2 " (have %d > %d)", P1, P2);                                                                                                                         \
    exit(1);                                                                                                                                                                                           \
  }


#define PARSE_RANGE_HEX(S, MIN, MAX) (\
		sscanf((S), "%x, %x", &(MIN), &(MAX)))


static char *search_type_to_str(search_type_t type)
{
	switch (type) {
		case SEARCH_TYPE_IV: return "ivs";
		case SEARCH_TYPE_IV_POKERUS: return "ivs & pokerus";
		case SEARCH_TYPE_TRAINER_SKIP: return "trainer skip";
		case SEARCH_TYPE_PLASMA_SKIP: return "plasma skip";
		default:
									   PRINT_ERROR("invalid search type: %u", type);
									   exit(1);
	}

}
static version_t get_version(const char *version)
{
	static const char *VERSIONS[VERSION_AMT] = {"black", "white", "black_2", "white_2"};

	for (size_t idx = 0; idx < VERSION_AMT; ++idx) {
		if (STR_EQ(version, VERSIONS[idx])) {
			return (version_t) idx;
		}
	}

	PRINT_ERROR("unknown version: %s", version);
	fprintf(stderr, "\tvalid versions: ");
	for (size_t idx = 0; idx < VERSION_AMT; ++idx) {
		fprintf(stderr, "%s%s", VERSIONS[idx], idx == VERSION_AMT - 1 ? "\n" : ", ");
	}

	exit(1);
}
static language_t get_language(const char *lang)
{
	static const char *LANGUAGES[LANG_AMT] = {"english", "japanese", "french", "italian", "german", "spanish", "korean"};

	for (size_t idx = 0; idx < LANG_AMT; ++idx) {
		if (STR_EQ(lang, LANGUAGES[idx])) {
			return (language_t) idx;
		}
	}

	PRINT_ERROR("unknown language: %s", lang);
	fprintf(stderr, "\tvalid languages: ");
	for (size_t idx = 0; idx < LANG_AMT; ++idx) {
		fprintf(stderr, "%s%s", LANGUAGES[idx], idx == LANG_AMT - 1 ? "\n" : ", ");
	}

	exit(1);
}

static search_type_t search_type_from_str(const char *search_type)
{
	static const char *SEARCH_TYPES[SEARCH_TYPE_AMT] = {"iv", "iv_pokerus", "trainer_skip", "plasma_skip"};

	for (size_t idx = 0; idx < SEARCH_TYPE_AMT; ++idx) {
		if (STR_EQ(search_type, SEARCH_TYPES[idx])) {
			return (search_type_t) idx;
		}
	}

	PRINT_ERROR("unknown search_type: %s", search_type);
	fprintf(stderr, "\tvalid search_types: ");
	for (size_t idx = 0; idx < SEARCH_TYPE_AMT; ++idx) {
		fprintf(stderr, "%s%s", SEARCH_TYPES[idx], idx == SEARCH_TYPE_AMT - 1 ? "\n" : ", ");
	}

	exit(1);
}



static int params_handler(void *out, const char *sec, const char *key, const char *value)
{
#define FMT_HEX(W) ("%w" #W "X")
#define FMT(W) ("%w" #W "u")

	params_t *params = (params_t *) out;

	/*
#define MAX_ENTRIES 10
	const struct {
		const char *section;
		struct {
			const char *key;
			const char *format_str;
			int (*callback)(void *, void *);
			void *ptr;
		} entries[MAX_ENTRIES];
	} LOOKUPS[] = {
		{
			.section = "parameters",
			.entries = {
			   	{
					.key = "mac_address",
					.format_str = FMT_HEX(64),
					.ptr = &params->mac_address,
				},
			   	{
					.key = "language",
					.callback = &lang_from_str,
					.ptr = &params->language,
				},
				{
					.key = "timer0_range",
					.format_str = FMT_HEX(32),
					.ptr = &params->timer0_range,
					
				}
			}
		},
	};
	// Pretty inefficient, though convenient
	for (size_t i = 0; i < sizeof(LOOKUPS) / sizeof(LOOKUPS[0]); ++i) {
		for (size_t j = 0; j < MAX_ENTRIES; ++j) {
			if (LOOKUPS[i].entries[j].key == NULL) {
				break;
			} 
			if (MATCH_KEY(LOOKUPS[i].entries[j].key)) {
				if (LOOKUPS[i].entries[j].callback != NULL) {
					LOOKUPS[i].entries[j].callback(value, LOOKUPS[i].entries[j].ptr);
				} else if (LOOKUPS[i].entries[j].format_str != NULL) {
					sscanf(value, LOOKUPS[i].entries[j].format_str, LOOKUPS[i].entries[j].ptr);
				}
			} 
		}
	}
	*/

	#define MATCH_SEC(SEC) (STR_EQ(sec, SEC))
	#define MATCH_KEY(KEY) (STR_EQ(key, KEY))

	
	if (MATCH_SEC("parameters")) {
		if (MATCH_KEY("mac_address")) {
			sscanf(value, "%w64X", &params->mac_address);
		} else if (MATCH_KEY("language")) {
			params->language = get_language(value);
		} else if (MATCH_KEY("version")) {
			params->version = get_version(value);
		} else if (MATCH_KEY("search_type")) {
			params->search_type = search_type_from_str(value);
		}
	} else if (MATCH_SEC("parameters.misc")) {
		if (MATCH_KEY("timer0_range")) {
			sscanf(value, "%w32X,%w32x", &params->min_timer0, &params->max_timer0);
		}
	} else if (MATCH_SEC("parameters.date_time")) {
		if (MATCH_KEY("year_range")) {
			sscanf(value, "%w16u,%w16u", &params->min_year, &params->max_year);
		} else if (MATCH_KEY("month_range")) {
			sscanf(value, "%w8u,%w8u", &params->min_month, &params->max_month);
		} else if (MATCH_KEY("day_range")) {
			sscanf(value, "%w8u,%w8u", &params->min_day, &params->max_day);
		} 

	}


#undef MAX_ENTRIES
#undef FMT
#undef FMT_HEX


	return 0;
}

params_t params_load(const char *path)
{
	params_t params;
	
	int ret;

	if ((ret = ini_parse(path, &params_handler, &params)) < 0) {
		PRINT_ERROR("couldn't load file \"%s\"; exiting", path);
		exit(ret);
	}

	params_print(stdout, &params);

	return params;
}

void params_validate(params_t *params) {
  printf("Validating parameters...");
  // TODO: asssert

  CHECK_VALID(params->max_keypresses, 0, 8);
  CHECK_VALID_RANGE(params->min_timer0, params->max_timer0);
  CHECK_VALID_RANGE(params->min_vcount, params->max_vcount);
  CHECK_VALID_RANGE(params->min_vframe, params->max_vframe);
  CHECK_VALID_RANGE(params->min_gxstat, params->max_gxstat);

  // Y/M/D
  {
    CHECK_VALID(params->min_year, 2000, 2099);
    CHECK_VALID(params->max_year, 2000, 2099);
    CHECK_VALID_RANGE(params->min_year, params->max_year);

    CHECK_VALID(params->min_month, 1, 12);
    CHECK_VALID(params->max_month, 1, 12);
    CHECK_VALID_RANGE(params->min_month, params->max_month);

    /* Assume the amount of days in a month is 31 */
    CHECK_VALID(params->min_day, 1, 31);
    CHECK_VALID(params->max_day, 1, 31);
    CHECK_VALID_RANGE(params->min_day, params->max_day);
  }

  // H:M:S
  {
    CHECK_VALID(params->min_hour, 0, 23);
    CHECK_VALID(params->max_hour, 0, 23);
    CHECK_VALID_RANGE(params->min_hour, params->max_hour);

    CHECK_VALID(params->min_minute, 0, 59);
    CHECK_VALID(params->max_minute, 0, 59);
    CHECK_VALID_RANGE(params->min_minute, params->max_minute);

    CHECK_VALID(params->min_second, 0, 59);
    CHECK_VALID(params->max_second, 0, 59);
    CHECK_VALID_RANGE(params->min_second, params->max_second);
  }

  puts("done!");
}

void params_set_default(params_t *params, version_t version) {
  {
    params->min_hour = params->min_minute = params->min_second = 0;

    params->max_hour = 23;

    params->max_minute = params->max_second = 59;

    params->min_month = 1;
    params->max_month = 12;

    params->min_day = 1;
    params->max_day = 31;

    params->min_year = 2000;
    params->max_year = 2099;
  }

  params->version = version == VERSION_NONE ? VERSION_WHITE_2 : version;

  params->language = LANG_ENG;

  params->min_gxstat = params->max_gxstat = 0x6;

  params->max_keypresses = 8;

  switch (params->version) {
  case VERSION_BLACK:
  case VERSION_WHITE:
    params->min_timer0 = 0xC79;
    params->max_timer0 = 0xC81;
    break;
  case VERSION_WHITE_2:
  case VERSION_BLACK_2:
    params->min_timer0 = 0x10F2;
    params->max_timer0 = 0x10F6;
    params->min_vcount = params->max_vcount = 0x82;
    params->min_vframe = params->max_vframe = 0x8;
    break;
  default:
    break;
  }
}

void params_print(FILE *stream, params_t *params)
{
	if (stream == NULL) {
		stream = stdout;
	}

	fprintf(stream, "parameters:\n");
	fprintf(stream, "\tmac address: %w64X\n", params->mac_address);
	fprintf(stream, "\tlanguage: %s (%d)\n", language_to_string(params->language), params->language);

	fprintf(stream, "\tversion: %s (%d)\n", version_to_string(params->version), params->version);

	fprintf(stream, "\ttimer0: %w32X-%w32X\n", params->min_timer0, params->max_timer0);
	fprintf(stream, "\tyear: %w16u-%w16u\n", params->min_year, params->max_year);
	fprintf(stream, "\tmonth: %w8u-%w8u\n", params->min_month, params->max_month);
	fprintf(stream, "\tday: %w8u-%w8u\n", params->min_day, params->max_day);

	fprintf(stream, "\tnazos: ");
	for (size_t i = 0; i < 5; ++i) {
		fprintf(stream, "%X ", NAZOS[params->language][params->version][i]);
	}
	fprintf(stream, "\n");

	fprintf(stream, "search settings:\n");
	fprintf(stream, "\tsearch type: %s\n", search_type_to_str(params->search_type));
}
