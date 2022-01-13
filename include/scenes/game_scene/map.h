#ifndef __MAP_H_
#define __MAP_H_

#include "tiles.h"

typedef struct
{
    void (*init)();
    void (*draw)();

    void (*set_resnder_view_port)(float cx, float cy);
    void (*mov_map_camera)(vec2f_t offset);

    float (*get_camera_height_blocks)();
    float (*get_block_height_gl)();

    Tile* (*getTile)(int x, int y);
} Map;

extern Map map;

#endif