#ifndef SEED_FINDER_LOCALE_KEYPRESSES_H
#define SEED_FINDER_LOCALE_KEYPRESSES_H

#include "utils/types.h"

#define KEYPRESS_AMT 2144

typedef struct keypress_s {
  u32 data;
  u8 button_amt;
  const char name[8][10];
} keypress_t;

extern const keypress_t KEYPRESSES[KEYPRESS_AMT];

#endif /* SEED_FINDER_LOCALE_KEYPRESSES_H */
