#ifndef __VEC_TYPES_H_
#define __VEC_TYPES_H_

#include<glad/glad.h>



typedef struct{
    float x, y, z, w;
} vec4f_t;

typedef struct{
    float x, y, z;
} vec3f_t;

typedef struct{
    float x;
    float y;
} vec2f_t;

typedef struct{
    vec4f_t r1, r2, r3, r4;
} mat4x4f_t;

vec4f_t vec4f(float x, float y, float z, float w);
vec3f_t vec3f(float x, float y, float z);
vec2f_t vec2f(float x, float y);

//x + y + z + w
float vec4f_sum(vec4f_t vec);
//x + y + z
float vec3f_sum(vec3f_t vec);
//x + y
float vec2f_sum(vec2f_t vec);

mat4x4f_t mat4x4f(vec4f_t r1, vec4f_t r2, vec4f_t r3, vec4f_t r4);

vec4f_t vec4f_mul(vec4f_t first, vec4f_t second);
vec3f_t vec3f_mul(vec3f_t first, vec3f_t second);
vec2f_t vec2f_mul(vec2f_t first, vec2f_t second);

mat4x4f_t mat4x4f_mul(mat4x4f_t first, mat4x4f_t second);

vec4f_t vec4f_add(vec4f_t first, vec4f_t second);
vec3f_t vec3f_add(vec3f_t first, vec3f_t second);
vec2f_t vec2f_add(vec2f_t first, vec2f_t second);

mat4x4f_t mat4x4f_add(mat4x4f_t first, mat4x4f_t second);

#endif