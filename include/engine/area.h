#ifndef SEED_FINDER_ENGINE_AREA_H
#define SEED_FINDER_ENGINE_AREA_H

struct map {

};

struct area {
	size_t map_amt;
	struct map *(maps[]);
	struct link *(links[]);
	struct trainer *(npcs[]);
};

#endif /* SEED_FINDER_ENGINE_AREA_H */
