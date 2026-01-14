#include "locale/version.h"

#include <stdlib.h>

const char *version_to_string(version_t version)
{
	switch (version) {
		case VERSION_BLACK: return "black";
		case VERSION_WHITE: return "white";
		case VERSION_BLACK_2: return "black_2";
		case VERSION_WHITE_2: return "white_2";
	}

	return NULL;
}
