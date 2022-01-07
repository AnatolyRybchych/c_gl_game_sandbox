#ifndef __SLIME_H_
#define __SLIME_H_

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../../drawable.h"
#include "../../shaders.h"
#include "../../gl_camera.h"

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
    
    GLuint shader_program;

} Slime;

extern Slime Player;

void init_player();

#endif