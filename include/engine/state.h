#ifndef SEED_FINDER_ENGINE_STATE_H
#define SEED_FINDER_ENGINE_STATE_H

#include "utils/types.h"
#include "engine/area.h"
#include "rng/rng.h"

typedef struct state_s {
	rng_t *rng;
	area_t *area;
	player_t *player;
} state_t;

#endif /* SEED_FINDER_ENGINE_STATE_H */
