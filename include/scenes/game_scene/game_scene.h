#ifndef __GAME_SCENE_H_
#define __GAME_SCENE_H_


#include "../../scene.h"
#include "../../texture2d.h"
#include "../../handle_queue.h"
#include "game_textures.h"
#include "tiles.h"
#include "slime.h"
#include "map.h"

#define MAP_SCALE 10.0f
#define BLOCK_SCALE (MAP_SCALE / BLOCKS_LOADING_DISTANCE_X)
#define SLIME_SCALE (SLIME_SIZE_BLOCKS * BLOCK_SCALE)

extern Scene GameScene;

#endif