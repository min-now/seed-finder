#ifndef SEED_FINDER_DATA_BW2_AREAS_H
#define SEED_FINDER_DATA_BW2_AREAS_H

enum { MAP_ID_ROUTE_21_NORTH, MAP_ID_ROUTE_21_SOUTH };

static const struct area_t AREA_ROUTE_21 = {
	.name      = "route 21",
	.flags     = AREA_FLAG_DUST_CLOUD,
	.loadlines = { {
		.axis      = AXIS_X,
		.offset    = 16,
		.linked_id = MAP_ID_ROUTE_21_SOUTH,
	} },
	.maps      = { { .base_coords = (struct coord_t) { .x = 0, .y = 192, .z = 0 } } }
};

#endif /* SEED_FINDER_DATA_BW2_AREAS_H */
