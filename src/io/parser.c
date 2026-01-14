#include <stdlib.h>
#include <errno.h>
#include <stdio.h>

#include "io/parser.h"
#include "io/profile.h"
#include "utils/macros.h"
#include "libs/inih/ini.h"

int parser_load_file(const char *path, ini_type_t type, void *data)
{
	// handle the FILE object separately as `ini_parse_file` doesn't output to stderr on error
	FILE *file = fopen(path, "r");

	if (file == nullptr) {
		PRINT_ERROR("couldn't open file %s: %s", path, strerror(errno));
		exit(errno);
	}

	/*
	switch (type) {
		// profile_t
		case INI_TYPE_PROFILE: 
		// job_t
		case INI_TYPE_JOB:

	}
	*/
	
	return EXIT_SUCCESS;
}
