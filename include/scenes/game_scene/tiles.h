#ifndef __TILES_H_
#define __TILES_H_

#include "tile.h"
#include "game_textures.h"
#include "../../shaders.h"

enum TILE
{
    TILE_DIRT,

    TILES_COUNT
};

extern Tile *Tiles[TILES_COUNT];

void init_tiles();

#endif