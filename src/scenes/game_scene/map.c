#include "../../../include/scenes/game_scene/map.h"


//methods
static void init();
static void draw();
static Tile* getTile(int x, int y);


//fields
int camera_pos_x, camera_pos_y;
float camera_pos_x_ex, camera_pos_x_ex;

int view_port_cx, view_port_cy;

Tile *cur_map_chunk[BLOCKS_LOADING_DISTANCE_X][BLOCKS_LOADING_DISTANCE_Y];


//instance
Map map = {
    .init = init,
    .draw = draw,
    .getTile = getTile,
};


//methods body
static void init()
{
    for(int x = 0; x < BLOCKS_LOADING_DISTANCE_X; x++)
    {
        for(int y = 0; y < BLOCKS_LOADING_DISTANCE_Y / 2; y ++)
        {
            cur_map_chunk[x][y] = Tiles[TILE_DIRT];
        }
    }

    cur_map_chunk[BLOCKS_LOADING_DISTANCE_X/2 - 10][BLOCKS_LOADING_DISTANCE_Y/2] = Tiles[TILE_DIRT];
    cur_map_chunk[BLOCKS_LOADING_DISTANCE_X/2 + 5][BLOCKS_LOADING_DISTANCE_Y/2] = Tiles[TILE_DIRT];
}

static void draw()
{
    gl_camera.push_state();

    gl_camera.scalef( 1.0 / BLOCKS_LOADING_DISTANCE_X );
    
    gl_camera.translate2f(vec2f(- BLOCKS_LOADING_DISTANCE_X, -BLOCKS_LOADING_DISTANCE_Y ));

    for(int x = 0; x < BLOCKS_LOADING_DISTANCE_X; x++)
    {
        for(int y = 0; y < BLOCKS_LOADING_DISTANCE_Y ; y ++)
        {
            if(cur_map_chunk[x][y])
                cur_map_chunk[x][y]->drawable.draw((Drawable*)cur_map_chunk[x][y]);
            gl_camera.translate2f(vec2f(0, 2));
        }
        gl_camera.translate2f(vec2f(0, - 2 * BLOCKS_LOADING_DISTANCE_Y));
        gl_camera.translate2f(vec2f(2, 0));
    }

    gl_camera.pop_state();
}


Tile* getTile(int x, int y)
{
    assert(x <  BLOCKS_LOADING_DISTANCE_X / 2);
    assert(x > -BLOCKS_LOADING_DISTANCE_X / 2);
    assert(y <  BLOCKS_LOADING_DISTANCE_Y / 2);
    assert(y > -BLOCKS_LOADING_DISTANCE_Y / 2);

    return cur_map_chunk[BLOCKS_LOADING_DISTANCE_X / 2 + x][BLOCKS_LOADING_DISTANCE_Y / 2 + y];
}