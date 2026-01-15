#ifndef SEED_FINDER_IO_PROFILE_H
#define SEED_FINDER_IO_PROFILE_H

#include "utils/types.h"
#include "io/parser.h"

#include "config/ds_params.h"

#include "locale/version.h"
#include "locale/language.h"

//#include "config/params.h"

/* 
 * Define date_time_t (and ds_params_t) in separate files to provide overridable configs
 * If a parameter is defined in both profile.ini and a job.ini, then the parameter defined job will take precedence 
 */
typedef struct profile_s {
	u64 mac_address;
	version_t version;
	language_t lang;

	ds_params_t ds_params;
} profile_t;


#endif /* SEED_FINDER_IO_PROFILE_H */
