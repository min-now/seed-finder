#ifndef SEED_FINDER_ENGINE_ACTION_H
#define SEED_FINDER_ENGINE_ACTION_H

#include "utils/types.h"

enum direction_e {
	DIR_UP = 0,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT,
};

enum movement_type_e : u16 {
	BIKE = 4,
	RUN = 8,
	SURF = RUN,
	WALK = 16,
};


// Types of actions

enum action_e : u16 {
	ACTION_MENU_OPEN = 0,
	ACTION_MENU_CLOSE,

	ACTION_TEXTBOX,
	ACTION_TEXTBOX_CLOSE,

	ACTION_NPC_TALK,

	ACTION_MOUNT_BIKE,
	ACTION_WALK,
	ACTION_SURF_START,
	ACTION_RUN,
	ACTION_TURNFRAME,

	ACTION_MOVEMENT,
	ACTION_VARIANCE
};

struct action_s {
	enum action_e type;
	union {
		struct {
			enum direction_e dir;
			enum movement_type_e mvmt_type;
			size_t amt;
		};
	};
} action_t;

#endif /* SEED_FINDER_ENGINE_ACTION_H */
