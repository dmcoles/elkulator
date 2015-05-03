/*
 * Data structures for handling paged/sideways RAM/ROM
 * Copyright (C) 2015, Richard Cook. All rights reserved.
 */

#ifndef _SIDEWAYS_BANK_H_INCLUDED
#define _SIDEWAYS_BANK_H_INCLUDED

#include <stdint.h>
#include "path.h"

// Typical sideways RAM/ROM allocation:
// F: ADFS (ROM)
// E: ???
// D: Sound Expansion (RAM)
// C: Plus 1 Expansion (ROM)
// B: BASIC (ROM)
// A: ???
// 9: ???
// 8: ???
// 7: User (RAM)
// 6: User (RAM)
// 5: User (ROM)
// 4: User (ROM)
// 3: DFS (RAM)
// 2: ???
// 1: User (ROM)
// 0: User (ROM)

#define SIDEWAYS_BANK_COUNT   16
#define SIDEWAYS_BANK_SIZE    16384
#define SIDEWAYS_BANK_F       0xF
#define SIDEWAYS_BANK_E       0xE
#define SIDEWAYS_BANK_D       0xD
#define SIDEWAYS_BANK_C       0xC
#define SIDEWAYS_BANK_B       0xB
#define SIDEWAYS_BANK_A       0xA
#define SIDEWAYS_BANK_9       0x9
#define SIDEWAYS_BANK_8       0x8
#define SIDEWAYS_BANK_7       0x7
#define SIDEWAYS_BANK_6       0x6
#define SIDEWAYS_BANK_5       0x5
#define SIDEWAYS_BANK_4       0x4
#define SIDEWAYS_BANK_3       0x3
#define SIDEWAYS_BANK_2       0x2
#define SIDEWAYS_BANK_1       0x1
#define SIDEWAYS_BANK_0       0x0

typedef enum
{
    SidewaysBankType_Empty,
    SidewaysBankType_Ram,
    SidewaysBankType_Rom
}
SidewaysBankType;

typedef struct
{
    SidewaysBankType type;
    char path[_MAX_PATH_WITH_NULL];
    uint8_t data[SIDEWAYS_BANK_SIZE];
}
SidewaysBankInfo;

extern SidewaysBankInfo g_sidewaysBanks[SIDEWAYS_BANK_COUNT];

#define SIDEWAYS_DATA(slot) \
    g_sidewaysBanks[SIDEWAYS_BANK_##slot].data
#define SIDEWAYS_BYTE(slot, addr) \
    g_sidewaysBanks[SIDEWAYS_BANK_##slot].data[addr]

#endif

