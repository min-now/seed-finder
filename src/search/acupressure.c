#include "search/acupressure.h"

#include "utils/macros.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// TODO: put somewhere else
static char *trim(char *str)
{
	if (str == NULL || *str == '\0') {
		return str;
	}

	while (isspace(*str)) {
		str++;
	}

	if (str == '\0') {
		return str;
	}


	char *end = str + strlen(str) - 1;
	while (end > str && isspace(*end)) {
		end--;
	}

	*(end + 1) = '\0';

	return str;
}

struct acupressure_ctx acupressure_init(const char *input)
{
	struct acupressure_ctx ctx;
	// max length: 21
	ctx.stat_order = malloc(sizeof(enum acupressure_stat));

	size_t i = 0;

	char *raw = trim(strtok(input, ","));
	while (raw != nullptr) {
		ctx.stat_order[i++] = acupressure_from_str(raw);
		//printf("%d ", ctx.stat_order[i-1]);
		raw = trim(strtok(NULL, ","));
	}
	ctx.length = i;

	return ctx;
}

enum acupressure_stat acupressure_from_str(const char *str)
{
	static const char *ACUPRESSURE_STATS[ACUPRESSURE_AMT] = {"attack", "defense", "speed", "sp.atk", "sp.def", "accuracy", "evasion"};

	for (size_t idx = 0; idx < ACUPRESSURE_AMT; ++idx) {
		if (STR_EQ(str, ACUPRESSURE_STATS[idx])) {
			return (enum acupressure_stat) idx;
		}
	}

	PRINT_ERROR("unknown stat: %s", str);
	fprintf(stderr, "\tvalid stats: ");
	for (size_t idx = 0; idx < ACUPRESSURE_AMT; ++idx) {
		fprintf(stderr, "%s%s", ACUPRESSURE_STATS[idx], idx == ACUPRESSURE_AMT - 1 ? "\n" : ", ");
	}

	exit(1);
}

const char *acupressure_to_str(enum acupressure_stat stat)
{
	switch (stat) {
		case ACUPRESSURE_ATTACK:
			return "attack";
		case ACUPRESSURE_DEFENSE:
			return "defense";
		case ACUPRESSURE_SPEED:
			return "speed";
		case ACUPRESSURE_SPATK:
			return "sp.atk";
		case ACUPRESSURE_SPDEF:
			return "sp.def";
		case ACUPRESSURE_ACCURACY:
			return "accuracy";
		case ACUPRESSURE_EVASION:
			return "evasion";
		default:
			return nullptr;
	}
}

bool acupressure_compare(struct acupressure_ctx *a, struct acupressure_ctx *b)
{
	for (int i = 0; i < MIN(a->length, b->length); ++i) {
		if (a->stat_order[i] != b->stat_order[i]) {
			return false;
		}
	}
	return true;
}

bool acupressure_compare_to_seed(u64 seed, struct acupressure_ctx *ctx)
{
	rng_t rng = rng_init(seed, VERSION_WHITE_2);

	struct { 
		enum acupressure_stat stat;
		u8 stage;
	} stats[ACUPRESSURE_AMT] = {
		{ACUPRESSURE_ATTACK, 0},
		{ACUPRESSURE_DEFENSE, 0},
		{ACUPRESSURE_SPEED, 0},
		{ACUPRESSURE_SPATK, 0},
		{ACUPRESSURE_SPDEF, 0},
		{ACUPRESSURE_ACCURACY, 0},
		{ACUPRESSURE_EVASION, 0}
	};

	// TODO
	for (size_t turn = 0, maxed = 0; turn < ctx->length; ++turn) {
		u32 n = rng_next_rand(&rng, ACUPRESSURE_AMT - maxed);

		stats[n].stage += 2;

//		printf("%d: %s\n", stats[n].stat, acupressure_to_str(stats[n].stat));
		
		if (ctx->stat_order[turn] != stats[n].stat) {
			return false;
		}

		if (stats[n].stage >= 6) {
			maxed++;
			for (int i = n; i < ACUPRESSURE_AMT - 1; ++i) {
				stats[i] = stats[i + 1];
			}
		}
	}

	return true;


}

void acupressure_from_seed(u64 seed, struct acupressure_ctx *ctx)
{
	rng_t rng = rng_init(seed, VERSION_NONE);

	struct { 
		enum acupressure_stat stat;
		u8 stage;
	} stats[ACUPRESSURE_AMT] = {
		{ACUPRESSURE_ATTACK, 0},
		{ACUPRESSURE_DEFENSE, 0},
		{ACUPRESSURE_SPEED, 0},
		{ACUPRESSURE_SPATK, 0},
		{ACUPRESSURE_SPDEF, 0},
		{ACUPRESSURE_ACCURACY, 0},
		{ACUPRESSURE_EVASION, 0}
	};

	// TODO
	ctx->length = 21; 
	ctx->stat_order = malloc(sizeof(enum acupressure_stat) * ctx->length);

	size_t turn = 0;
	printf("\n\n");
	for (int pp = 30, maxed = 0; pp > 9; --pp) {
		u32 n = rng_next_rand(&rng, ACUPRESSURE_AMT - maxed);

		stats[n].stage += 2;

//		printf("%s, ", acupressure_to_str(stats[n].stat));
		ctx->stat_order[turn] = stats[n].stat;

		if (stats[n].stage >= 6) {
			maxed++;
			for (int i = n; i < STAT_AMT - 1; ++i) {
				stats[i] = stats[i + 1];
			}
		}
		turn++;
	}
}



