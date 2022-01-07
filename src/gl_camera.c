#include "../include/gl_camera.h"


void translate3f(vec3f_t vec);
void translate2f(vec2f_t vec);

void scale3f(vec3f_t vec);
void scale2f(vec2f_t vec);
void scalef(float value);

void rotate3f(vec3f_t vec);
void rotatef(float angle);

void push_state();
void pop_state();

void uniform(GLint MVP_pos);


mat4x4f_t State = {
    {1.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 1.0f},
};

mat4x4f_t StateStack[CAMERA_STATE_STACK_LEN];
mat4x4f_t *StateStackPtr = &(StateStack[0]);



void translate3f(vec3f_t vec)
{
    State = mat4x4f_mul(State, mat4x4f( vec4f(1, 0, 0, vec.x),
                                        vec4f(0, 1, 0, vec.y),
                                        vec4f(0, 0, 1, vec.z),
                                        vec4f(0, 0, 0, 1)));
}

void translate2f(vec2f_t vec)
{
    State = mat4x4f_mul(State, mat4x4f( vec4f(1, 0, 0, vec.x),
                                        vec4f(0, 1, 0, vec.y),
                                        vec4f(0, 0, 1, 0),
                                        vec4f(0, 0, 0, 1)));
}

void scale3f(vec3f_t vec)
{
    State = mat4x4f_mul(State, mat4x4f( vec4f(vec.x, 0, 0, 0),
                                        vec4f(0, vec.y, 0, 0),
                                        vec4f(0, 0, vec.z, 0),
                                        vec4f(0, 0, 0    , 1)));
}
void scale2f(vec2f_t vec)
{
    State = mat4x4f_mul(State, mat4x4f( vec4f(vec.x, 0, 0, 0),
                                        vec4f(0, vec.y, 0, 0),
                                        vec4f(0, 0, 1, 0),
                                        vec4f(0, 0, 0, 1)));
}
void scalef(float value)
{
    State = mat4x4f_mul(State, mat4x4f( vec4f(value , 0      , 0 , 0),
                                        vec4f(0     , value  , 0 , 0),
                                        vec4f(0     , 0      , 1 , 0),
                                        vec4f(0     , 0      , 0 , 1)));
}

void rotate3f(vec3f_t vec)
{
    mat4x4f_t rotation_mat = mat4x4f(
        vec4f(cosf(vec.x) * cosf(vec.y)    , cosf(vec.x) * sinf(vec.y) * sinf(vec.z) - sinf(vec.x) * cosf(vec.z)       , cosf(vec.x) * sinf(vec.y) * cosf(vec.z) + sinf(vec.x) * sinf(vec.z), 0), 
        vec4f(sinf(vec.x) * sinf(vec.x)    , sinf(vec.y) * sinf(vec.z) * sinf(vec.z) + cosf(vec.x) * cosf(vec.z)       , sinf(vec.x) * sinf(vec.y) * cosf(vec.z) - cosf(vec.x) * sinf(vec.z), 0),
        vec4f(- sinf(vec.y)                , cosf(vec.y) * sinf(vec.z)                                                 , cosf(vec.y) * cosf(vec.z), 0),
        vec4f(0, 0, 0, 1)
        );
    State = mat4x4f_mul(State, rotation_mat);
}

void rotatef(float angle)
{
    State = mat4x4f_mul(State, mat4x4f( vec4f(cosf(angle)   , -sinf(angle) , 0, 0),
                                        vec4f(sinf(angle)   , cosf(angle)  , 0, 0),
                                        vec4f(0             , 0            , 1, 0),
                                        vec4f(0             , 0            , 0, 1)));
}

void push_state()
{
    if(StateStackPtr++ >= StateStack + CAMERA_STATE_STACK_LEN)
    {
        fprintf(stderr, "ERROR: gl_camera StateStack overflow\n");
        exit(EXIT_FAILURE);
    }

    *StateStackPtr = State;
}
void pop_state()
{
    if(StateStackPtr == StateStack)
    {
        fprintf(stderr, "WARNING: gl_camera StateStack empty pop\n");
        State = (mat4x4f_t){
            {1.0f, 0.0f, 0.0f, 0.0f},
            {0.0f, 1.0f, 0.0f, 0.0f},
            {0.0f, 0.0f, 1.0f, 0.0f},
            {0.0f, 0.0f, 0.0f, 1.0f},
        };
    }
    else
    {
        State = *StateStackPtr;
        StateStackPtr--;
    }
}

void uniform(GLint MVP_pos)
{
    glUniformMatrix4fv(MVP_pos, 1, GL_TRUE, (GLfloat*)&State);
}


gl_camera_functions gl_camera = {
    .translate2f = translate2f,
    .translate3f = translate3f,

    .scale3f = scale3f,
    .scale2f = scale2f,
    .scalef = scalef,

    .rotate3f = rotate3f,
    .rotatef = rotatef,

    .push_state = push_state,
    .pop_state = pop_state,

    .uniform = uniform,
};