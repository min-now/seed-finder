#ifndef SEED_FINDER_ENGINE_TRAINER_H
#define SEED_FINDER_ENGINE_TRAINER_H

#include "rng/rng.h"
#include "utils/macros.h"
#include "utils/types.h"

#include <stdlib.h>

#define MAX_TRAINER_CLASS_LEN 20
#define MAX_TRAINER_NAME_LEN  20
#define MAX_DIRS              4

constexpr static u8 TRAINER_TIMERS[4] = {16, 32, 48, 64};

enum trainer_dir_e {
	DIR_NONE = 0,

	DIR_UP    = 1 << 1,
	DIR_DOWN  = 1 << 2,
	DIR_LEFT  = 1 << 3,
	DIR_RIGHT = 1 << 4,

	DIR_ALL = DIR_UP | DIR_DOWN | DIR_LEFT | DIR_RIGHT
};

enum trainer_status_e {
	TRAINER_STATUS_UNLOADED,
	TRAINER_STATUS_LOADED,
	TRAINER_STATUS_ACTIVE
};

enum trainer_type_e {
	TRAINER_TYPE_SPINNER      = 0,
	TRAINER_TYPE_SPINNER_DEAF = 2,
	TRAINER_TYPE_WALKER       = 8,
	//	TRAINER_TYPE_WALKER_DEAF = 8,
	TRAINER_TYPE_STATIC = 10,
};

struct trainer_t {
	u8 timer;
	u8 delay;
	const s8 extra_adv;

	enum trainer_status_e status;
	enum trainer_dir_e dir;
	enum trainer_type_e type;

	const enum trainer_dir_e dirs[MAX_DIRS];
	u8 dirs_amt;

	const char class[MAX_TRAINER_CLASS_LEN];
	const char name[MAX_TRAINER_NAME_LEN];

	void (*advance)(struct trainer_t *, struct rng_t *);

	void (*load)(struct trainer_t *, struct rng_t *);

	void (*unload)(struct trainer_t *);
	void (*activate)(struct trainer_t *);
};

void trainer_init(struct trainer_t *trainer);

void trainer_advance(struct trainer_t *trainer, struct rng_t *rng);

void trainer_load(struct trainer_t *trainer, struct rng_t *rng);
void trainer_unload(struct trainer_t *trainer);

void trainer_activate(struct trainer_t *trainer);

void trainer_new_timer(struct trainer_t *trainer, struct rng_t *rng);
void trainer_new_dir(struct trainer_t *trainer, struct rng_t *rng);

#endif /* SEED_FINDER_ENGINE_TRAINER_H */
