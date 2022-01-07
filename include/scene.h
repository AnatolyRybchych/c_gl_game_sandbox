#ifndef __SCENE_H_
#define __SCENE_H_

#include "window.h"

#include "shader_program.h"
#include "shaders.h"
#include "texture2d.h"

typedef struct __SCENE_T Scene;

struct __SCENE_T{
    void (*init)();
    void (*on_frame)(RenderContext *context);
    void (*close)();
};

#endif