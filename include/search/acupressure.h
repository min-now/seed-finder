#ifndef SEED_FINDER_SEARCH_ACUPRESSURE_H
#define SEED_FINDER_SEARCH_ACUPRESSURE_H

#define STAT_AMT 7

#include "utils/types.h"
#include "rng/rng.h"

enum acupressure_stat : u8 {
	ACUPRESSURE_ATTACK = 0,
	ACUPRESSURE_DEFENSE,
	ACUPRESSURE_SPEED,
	ACUPRESSURE_SPATK,
	ACUPRESSURE_SPDEF,
	ACUPRESSURE_ACCURACY,
	ACUPRESSURE_EVASION,
	ACUPRESSURE_AMT,
};

struct acupressure_ctx {
	enum acupressure_stat *stat_order;
	size_t length;
};

bool acupressure_compare(struct acupressure_ctx *a, struct acupressure_ctx *b);

enum acupressure_stat acupressure_from_str(const char *str);

const char *acupressure_to_str(enum acupressure_stat stat);


void acupressure_from_seed(u64 seed, struct acupressure_ctx *ctx);

struct acupressure_ctx acupressure_init(const char *input);

bool acupressure_compare_to_seed(u64 seed, struct acupressure_ctx *ctx);

#endif /* SEED_FINDER_SEARCH_ACUPRESSURE_H */
