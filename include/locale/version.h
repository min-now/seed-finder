#ifndef SEED_FINDER_LOCALE_VERSION_H
#define SEED_FINDER_LOCALE_VERSION_H

#define GAME_VERSION_AMT 4

#define VERSION_AMT 4

typedef enum version_e {
  VERSION_BLACK = 0,
  VERSION_WHITE,

  VERSION_BLACK_2,
  VERSION_WHITE_2,

  VERSION_NONE,
} version_t;

const char *version_to_string(version_t version);

#endif /* SEED_FINDER_LOCALE_VERSION_H */
