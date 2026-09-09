#ifndef SEED_FINDER_ENGINE_ACTION_H
#define SEED_FINDER_ENGINE_ACTION_H

#include "utils/types.h"

/*
typedef enum direction_e {
	DIR_NONE
	DIR_UP = 0,
	DIR_DOWN
};
*/

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
};

struct action {
	enum action_type type;

};

#endif /* SEED_FINDER_ENGINE_ACTION_H */
