#ifndef SEED_FINDER_IO_PARSER_H
#define SEED_FINDER_IO_PARSER_H

#include "libs/inih/ini.h"

typedef enum ini_type_e {
	INI_TYPE_PROFILE,
	INI_TYPE_JOB,
} ini_type_t;

int parser_load_file(const char *path, ini_type_t type, void *data);

// from ini.h: typedef char* (*ini_reader)(char* str, int num, void* stream);
// `int num` is max_line
int parser_read(const char *restrict path);

#endif /* SEED_FINDER_IO_PARSER_H */
