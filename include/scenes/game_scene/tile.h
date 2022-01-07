#ifndef __TILE_H_
#define __TILE_H_

#include <glad/glad.h>

#include "../../disposable.h"
#include "../../drawable.h"
#include "../../gl_camera.h"


typedef struct __TILE_T Tile;

//shader_program should have:
//---------------------------------
//uniform sampler2D tex1;
//uniform mat4 MVP;
//---------------------------------
Tile new_tile(GLuint texture, GLuint shader_program);

struct __TILE_T
{
    //should be in top///////
    Drawable drawable;
    /////////////////////////
    Disposable disposable;

    GLuint texture;
    GLuint shader_program;

};

#endif