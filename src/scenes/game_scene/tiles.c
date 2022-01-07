#include "../../../include/scenes/game_scene/tiles.h"

enum STD_TILE{
    STD_TILE_DIRT,

    STD_TILE_CNT,
};

Tile StdTiles[STD_TILE_CNT];


Tile *Tiles[TILES_COUNT];


void init_tiles()
{
    StdTiles[STD_TILE_DIRT] = new_tile(GameSceneTextures[TEXTURE_DIRT_DEF], ShaderPrograms[DEFAULT_SHADER_PROGRAM]);


    
    Tiles[TILE_DIRT] = &StdTiles[STD_TILE_DIRT];


}