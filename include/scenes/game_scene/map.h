#ifndef __MAP_H_
#define __MAP_H_

#define MAP_SCALE 10.0f
#define BLOCKS_LOADING_DISTANCE_X 100
#define BLOCKS_LOADING_DISTANCE_Y BLOCKS_LOADING_DISTANCE_X

#define BLOCK_SCALE (MAP_SCALE / BLOCKS_LOADING_DISTANCE_X)
#define SLIME_SCALE (SLIME_SIZE_BLOCKS * BLOCK_SCALE)

#include "tiles.h"

typedef struct
{
    void (*init)();
    void (*draw)();
    void (*translate)(vec2f_t offset_blocks);
    void (*set_scale)(float scale);

    Tile* (*getTile)(int x, int y);
} Map;

extern Map map;

#endif