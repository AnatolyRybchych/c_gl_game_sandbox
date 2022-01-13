#include "../../../include/scenes/game_scene/map.h"

#define BLOCKS_LOADING_DISTANCE_X 1000
#define BLOCKS_LOADING_DISTANCE_Y BLOCKS_LOADING_DISTANCE_X


//methods
static void init();


//fields
int camera_pos_x, camera_pos_y;
float camera_pos_x_ex, camera_pos_x_ex;

int view_port_cx, view_port_cy;

Tile *cur_map_chunk[BLOCKS_LOADING_DISTANCE_X][BLOCKS_LOADING_DISTANCE_Y];


//instance
Map map = {
    .init = init,
};


//methods body
static void init()
{

}