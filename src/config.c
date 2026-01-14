#include "config.h"
#include "inih/ini.h"
#include "utils/macros.h"

#define MATCH_SEC(SEC) (STR_EQ(sec, SEC))
#define MATCH_KEY(KEY) (STR_EQ(key, KEY))

static int config_handler(void *out, const char *sec, const char *key, const char *value)
{


	return 0;
}


#undef MATCH_SEC
#undef MATCH_KEY


