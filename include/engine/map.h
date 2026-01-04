#ifndef SEED_FINDER_ENGINE_MAP_H
#define SEED_FINDER_ENGINE_MAP_H

#include "utils/types.h"
#include "engine/trainer.h"

#define MAX_AREA_NAME_LENGTH 20
#define MAX_AREA_LOADLINES   4
#define MAX_MAP_TRAINERS     15

#define MAX_AREA_MAPS 10

enum area_flags_e { AREA_FLAG_DUST_CLOUD = 1 << 1 };

enum axis_e { AXIS_X, AXIS_Y };

struct coord_t {
	union {
		struct {
			u8 x, y, z;
		};
		u8 raw[3];
	};
};

struct loadline_t {
	const enum axis_e axis;
	u8 offset;
	u8 linked_id;
};

struct map_t {
	u8 id;
	struct coord_t base_coords;

	struct trainer_t trainers[MAX_MAP_TRAINERS];
	//	struct trainer_t trainers[MAX_MAP_TRAINERS];
};

struct area_t {
	const char name[MAX_AREA_NAME_LENGTH];
	const enum area_flags_e flags;

	struct loadline_t loadlines[MAX_AREA_LOADLINES];

	struct map_t maps[MAX_AREA_MAPS];
};

#include "data/bw2_areas.h"

#endif /* SEED_FINDER_ENGINE_MAP_H */
