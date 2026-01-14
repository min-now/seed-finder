#ifndef SEED_FINDER_IO_PROFILE_H
#define SEED_FINDER_IO_PROFILE_H

#include "utils/types.h"
#include "io/parser.h"
#include "locale/version.h"
#include "locale/language.h"

//#include "config/params.h"

typedef struct profile_s {
	u64 mac_address;
	version_t version;
	language_t lang;

//	params_t params;
} profile_t;


#endif /* SEED_FINDER_IO_PROFILE_H */
