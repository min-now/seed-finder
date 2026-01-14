#ifndef SEED_FINDER_LOCALE_LANGUAGE_H
#define SEED_FINDER_LOCALE_LANGUAGE_H

#include <string.h>

#define LANG_AMT 7

typedef enum language_e { LANG_ENG = 0, LANG_JPN, LANG_FRA, LANG_ITA, LANG_GER, LANG_SPA, LANG_KOR } language_t;

const char *language_to_string(language_t lang);

static inline int lang_from_str(const char *lang, language_t *language)
{
	static const char *LANGUAGES[LANG_AMT] = {"english", "japanese", "french", "italian", "german", "spanish", "korean"};

	for (size_t idx = 0; idx < LANG_AMT; ++idx) {
		if (strcmp(lang, LANGUAGES[idx]) == 0) {
			*language = (language_t) idx;
			return 0;
		}
	}
	
	return 1;
}



#endif /* SEED_FINDER_LOCALE_LANGUAGE_H */
