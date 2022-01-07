#ifndef __SCENES_H_
#define __SCENES_H_

#include "scene.h"

#include "../include/scenes/game_scene/game_scene.h"

enum SCENE{
    SCENE_GAME,

    SCENES_COUNT,
};

extern Scene *Scenes[SCENES_COUNT];



#endif