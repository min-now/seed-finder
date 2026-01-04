#ifndef SEED_FINDER_ENGINE_COORDS_H
#define SEED_FINDER_ENGINE_COORDS_H

#include "utils/types.h"

struct position_t {
	union {
		struct {
			u8 x, y, z;
		};
		u8 raw[3];
	};
};

#endif /* SEED_FINDER_ENGINE_COORDS_H */
