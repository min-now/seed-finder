#ifndef SEED_FINDER_IO_JOB_H
#define SEED_FINDER_IO_JOB_H

#include "utils/types.h"
#include "config/ds_params.h"

typedef enum job_type_e : u32 {
	JOB_TYPE_IV 			= 1 << 1,
	JOB_TYPE_POKERUS 		= JOB_TYPE_IV + 1,
	JOB_TYPE_TRAINER_SKIP	= 1 << 2,
	JOB_TYPE_PLASMA_SKIP	= 1 << 3,
} job_type_t;

typedef struct job_s {
	job_type_t type;

	// Probably rename field to params
	ds_params_t ds_params;
} job_t;



#endif /* SEED_FINDER_IO_JOB_H */
