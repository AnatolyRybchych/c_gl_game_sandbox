#ifndef __MAP_H_
#define __MAP_H_

#define BLOCKS_LOADING_DISTANCE_X 100
#define BLOCKS_LOADING_DISTANCE_Y BLOCKS_LOADING_DISTANCE_X

#include "tiles.h"

typedef struct
{
    void (*init)();
    void (*draw)();

    Tile* (*getTile)(int x, int y);
} Map;

extern Map map;

#endif