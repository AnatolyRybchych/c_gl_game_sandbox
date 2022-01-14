#ifndef __SLIME_H_
#define __SLIME_H_


#include<math.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../drawable.h"
#include "../../shaders.h"
#include "../../gl_camera.h"
#include "../../window.h"
#include "tiles.h"
#include "map.h"
#include "game_scene.h"

#define SLIME_SIZE_BLOCKS 4
#define SLIME_OVERSIZE 1.3f
#define DEFAULT_SLIME_BREATH_SPEED 1.5

typedef struct
{
    //Should be in top
    Drawable drawable;
    //////////////////
    float x,y,scale;
    float collision_left;
    float collision_right;
    float breath_speed;

    void (*handle_activity)(RenderContext *context);
    
    GLuint shader_program;

} Slime;

extern Slime Player;

void init_player();

#endif