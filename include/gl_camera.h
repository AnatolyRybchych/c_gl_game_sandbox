#ifndef __GL_CAMERA_H_
#define __GL_CAMERA_H_

#include<math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/glad.h>
#include "vec_types.h" 

#ifndef CAMERA_STATE_STACK_LEN
    #define CAMERA_STATE_STACK_LEN 1000
#endif


typedef struct 
{
    //increases current translation.xyz by value
    void (*translate3f)(vec3f_t vec);
    //increases current translation.xy by value
    void (*translate2f)(vec2f_t vec);

    //multiplys current scale with new
    void (*scale3f)(vec3f_t vec);
    //multiplys current scale with new
    void (*scale2f)(vec2f_t vec);
    //multiplys current scale with new
    void (*scalef)(float value);

    //increases current rotation using vector
    void (*rotate3f)(vec3f_t vec);
    //increases current rotation by value
    void (*rotatef)(float angle);

    //push current state to state stack stacksize is CAMERA_STATE_STACK_LEN (#define CAMERA_STATE_STACK_LEN Value before include to change)
    void (*push_state)();
    //pop current state from state stack 
    void (*pop_state)();

    void (*uniform)(GLint MVP_pos);
} gl_camera_functions;

extern gl_camera_functions gl_camera; 


#endif