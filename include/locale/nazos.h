#ifndef SEED_FINDER_LOCALE_NAZOS_H
#define SEED_FINDER_LOCALE_NAZOS_H

#include "locale/language.h"
#include "locale/version.h"
#include "utils/macros.h"
#include "utils/types.h"

/* https://github.com/Admiral-Fish/PokeFinder/blob/master/Core/Gen5/Nazos.cpp */

#define COMPUTE_NAZO_BW1(NAZO) {BSWAP(NAZO), BSWAP(NAZO + 0xFC), BSWAP(NAZO + 0xFC), BSWAP(NAZO + 0x148), BSWAP(NAZO + 0x148)}

#define COMPUTE_NAZO_BW2(N1, N2, N3) {BSWAP(N2), BSWAP(N3), BSWAP(N1), BSWAP(N1 + 0x54), BSWAP(N1 + 0x54)}

static const u32 NAZOS[LANG_AMT][VERSION_AMT][5] = {
    [LANG_ENG] =
        {
                    [VERSION_BLACK] = COMPUTE_NAZO_BW1(0x022160B0),
                    [VERSION_WHITE] = COMPUTE_NAZO_BW1(0x022160D0),
                    [VERSION_BLACK_2] = COMPUTE_NAZO_BW2(0x02200010,                          0x0209AEE8, 0x02039DE9),
                    [VERSION_WHITE_2] = COMPUTE_NAZO_BW2(0x02200050,                                       0x0209AF28,0x02039E15),
                    },
    [LANG_JPN] =
        {
                    [VERSION_BLACK] = COMPUTE_NAZO_BW1(0x02215F10),
                    [VERSION_WHITE] = COMPUTE_NAZO_BW1(0x02215F30),
                    [VERSION_BLACK_2] = COMPUTE_NAZO_BW2(0x021FF9B0,                           0x0209A8DC,                                       0x02039AC9),
                    [VERSION_WHITE_2] = COMPUTE_NAZO_BW2(0x021FF9D0, 0x0209A8FC,0x02039AF5),
                    },
    [LANG_FRA] =
        {
                    [VERSION_BLACK] = COMPUTE_NAZO_BW1(0x02216030),
                    [VERSION_WHITE] = COMPUTE_NAZO_BW1(0x02216050),
                    [VERSION_BLACK_2] = COMPUTE_NAZO_BW2(0x02200030,                                                                        0x0209AF08,                                                                                                         0x02039DF9),
                    [VERSION_WHITE_2] = COMPUTE_NAZO_BW2(0x02200050,                                        0x0209AF28,0x02039E25),
                    },
    [LANG_ITA] =
        {
                    [VERSION_BLACK] = COMPUTE_NAZO_BW1(0x02215FB0),
                    [VERSION_WHITE] = COMPUTE_NAZO_BW1(0x02215FD0),
                    [VERSION_BLACK_2] = COMPUTE_NAZO_BW2(0x021FFF10,              0x0209ADE8,            0x02039D69),
                    [VERSION_WHITE_2] = COMPUTE_NAZO_BW2(0x021FFF50,                                                                                                          0x0209AE28,0x02039D95),
                    },
    [LANG_GER] =
        {
                    [VERSION_BLACK] = COMPUTE_NAZO_BW1(0x02215FF0),
                    [VERSION_WHITE] = COMPUTE_NAZO_BW1(0x02216010),
                    [VERSION_BLACK_2] = COMPUTE_NAZO_BW2(0x021FFF50,0x0209AE28,                                      0x02039D69),
                    [VERSION_WHITE_2] = COMPUTE_NAZO_BW2(0x021FFF70,0x0209AE48,0x02039D95),
                    },
    [LANG_SPA] =
        {
                    [VERSION_BLACK] = COMPUTE_NAZO_BW1(0x02216070),
                    [VERSION_WHITE] = COMPUTE_NAZO_BW1(0x02216070),
                    [VERSION_BLACK_2] = COMPUTE_NAZO_BW2(0x021FFFD0,                          0x0209AEA8,                                       0x02039DB9),
                    [VERSION_WHITE_2] = COMPUTE_NAZO_BW2(0x021FFFF0,                                       0x0209AEC8, 0x02039DE5),
                    },
    [LANG_KOR] = {
                    [VERSION_BLACK] = COMPUTE_NAZO_BW1(0x022167B0),
                    [VERSION_WHITE] = COMPUTE_NAZO_BW1(0x022167B0),
                    [VERSION_BLACK_2] = COMPUTE_NAZO_BW2(0x02200750,                           0x0209B60C,                                       0x0203A4D5),
                    [VERSION_WHITE_2] = COMPUTE_NAZO_BW2(0x02200770,  0x0209B62C,0x0203A501),
                    }
};

#endif /* SEED_FINDER_LOCALE_NAZOS_H */
