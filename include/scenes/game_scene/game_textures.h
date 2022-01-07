#ifndef __GAME_TEXTURES_H_
#define __GAME_TEXTURES_H_

#include <glad/glad.h>
#include "../../texture2d.h"

#ifdef _DEBUG
    #define DEBUG_PARENT "build/out/"
#else
    #define DEBUG_PARENT ""
#endif

#define TEXTURES_DIR DEBUG_PARENT"scenes/game_scene/sprites/"

enum GAME_SCENE_TEXTURE{
    TEXTURE_DIRT_DEF,

    TEXTURES_COUNT,
};

extern GLuint GameSceneTextures[TEXTURES_COUNT];
void load_textures_game_scene();

#endif