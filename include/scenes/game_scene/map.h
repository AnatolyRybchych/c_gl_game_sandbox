#ifndef __MAP_H_
#define __MAP_H_

#include "tiles.h"

typedef struct
{
    void (*init)();
    void (*draw)();

    Tile* (*getTile)(int x, int y);
} Map;

extern Map map;

#endif