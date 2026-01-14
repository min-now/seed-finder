#ifndef SEED_FINDER_SEARCH_H
#define SEED_FINDER_SEARCH_H

#include "utils/types.h"
#include "locale/params.h"
#include "utils/macros.h"
#include "rng/seed.h"

extern const u8 NO_WEATHER_DATES[12][31];

// typedef bool (*callback_t)(u64 seed, struct parameters_t *);

/*
#define MAX_LIST_SIZE

#define darray_new(type, size)\
	struct {				\
		type 

	}
*/

typedef struct search_ctx_s {
	seed_t seed;
	search_type_t search_type;

} search_ctx_t;

void generate(params_t *params);

#endif /* SEED_FINDER_SEARCH_H */
