#include "locale/language.h"
#include <stdlib.h>

const char *language_to_string(language_t lang)
{
	switch (lang) {
		case LANG_ENG: return "english";
		case LANG_JPN: return "japanese";
		case LANG_FRA: return "french";
		case LANG_ITA: return "italian";
		case LANG_GER: return "german";
		case LANG_SPA: return "spanish";
		case LANG_KOR: return "korean";
	}

	return NULL;
}

