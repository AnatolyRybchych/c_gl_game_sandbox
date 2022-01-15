#include "../../../include/scenes/game_scene/map.h"


//methods
static void init();
static void draw();
static Tile* getTile(int x, int y);
static void translate(vec2f_t offset_blocks);
static void set_scale(float scale);


//fields
static int camera_pos_x, camera_pos_y;
static float camera_pos_x_ex, camera_pos_y_ex;

static float camera_scale;

static int view_port_cx, view_port_cy;

static Tile *cur_map_chunk[BLOCKS_LOADING_DISTANCE_X][BLOCKS_LOADING_DISTANCE_Y];


//instance
Map map = {
    .init = init,
    .draw = draw,
    .getTile = getTile,
    .translate = translate,
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

    camera_pos_x = 0;
    camera_pos_y = 0;
    camera_pos_x_ex = 0;
    camera_pos_y_ex = 0;
    camera_scale = MAP_SCALE;

    cur_map_chunk[BLOCKS_LOADING_DISTANCE_X/2 - 10][BLOCKS_LOADING_DISTANCE_Y/2] = Tiles[TILE_DIRT];
    cur_map_chunk[BLOCKS_LOADING_DISTANCE_X/2 + 5][BLOCKS_LOADING_DISTANCE_Y/2] = Tiles[TILE_DIRT];
}

static void draw()
{
    gl_camera.push_state();

    gl_camera.translate2f(vec2f((camera_pos_x_ex + camera_pos_x) * BLOCK_SCALE, (camera_pos_y_ex + camera_pos_y )* BLOCK_SCALE));

    printf("%f,%f\n", camera_pos_x, camera_pos_y);

    gl_camera.scalef( camera_scale / BLOCKS_LOADING_DISTANCE_X );
    
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

void translate(vec2f_t offset_blocks)
{
    camera_pos_x_ex += offset_blocks.x / BLOCK_SCALE;
    camera_pos_y_ex += offset_blocks.y / BLOCK_SCALE;

    camera_pos_x += (int)camera_pos_x_ex; 
    camera_pos_y += (int)camera_pos_y_ex;

    camera_pos_y_ex -= (int)camera_pos_y_ex;
    camera_pos_x_ex -= (int)camera_pos_x_ex;
}