#ifndef SEED_FINDER_CONFIG_H
#define SEED_FINDER_CONFIG_H

#include "utils/macros.h"

#define MATCH_SEC(SEC) (STR_EQ(sec, SEC))
#define MATCH_KEY(KEY) (STR_EQ(key, KEY))



#undef MATCH_SEC
#undef MATCH_KEY

#endif /* SEED_FINDER_CONFIG_H */
