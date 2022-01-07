#include "../include/vec_types.h"

#define MAT4x4_COLUMN1(mat) vec4f(mat.r1.x, mat.r2.x, mat.r3.x, mat.r4.x)
#define MAT4x4_COLUMN2(mat) vec4f(mat.r1.y, mat.r2.y, mat.r3.y, mat.r4.y)
#define MAT4x4_COLUMN3(mat) vec4f(mat.r1.z, mat.r2.z, mat.r3.z, mat.r4.z)
#define MAT4x4_COLUMN4(mat) vec4f(mat.r1.w, mat.r2.w, mat.r3.w, mat.r4.w)
//constructors 

vec4f_t vec4f(float x, float y, float z, float w)
{
        return (vec4f_t){
        .x = x,
        .y = y,
        .z = z,
        .w = w,
    };
}

vec3f_t vec3f(float x, float y, float z)
{
    return (vec3f_t){
        .x = x,
        .y = y,
        .z = z,
    };
};

vec2f_t vec2f(float x, float y)
{
    return (vec2f_t){
        .x = x,
        .y = y,
    };
};

float vec4f_sum(vec4f_t vec)
{
    return vec.x + vec.y + vec.z + vec.w;
}

float vec3f_sum(vec3f_t vec)
{
    return vec.x + vec.y + vec.z;
}

float vec2f_sum(vec2f_t vec)
{
    return vec.x + vec.y;
}

mat4x4f_t mat4x4f(vec4f_t r1, vec4f_t r2, vec4f_t r3, vec4f_t r4)
{
    return (mat4x4f_t){
        .r1 = r1,
        .r2 = r2,
        .r3 = r3,
        .r4 = r4,
    };
}



//multily functions
vec4f_t vec4f_mul(vec4f_t first, vec4f_t second)
{
        return (vec4f_t){
        .x = first.x * second.x,
        .y = first.y * second.y,
        .z = first.z * second.z,
        .w = first.w * second.w,
    };
}

vec3f_t vec3f_mul(vec3f_t first, vec3f_t second)
{
    return (vec3f_t){
        .x = first.x * second.x,
        .y = first.y * second.y,
        .z = first.z * second.z,
    };
};

vec2f_t vec2f_mul(vec2f_t first, vec2f_t second)
{
    return (vec2f_t){
        .x = first.x * second.x,
        .y = first.y * second.y,
    };
};


mat4x4f_t mat4x4f_mul(mat4x4f_t first, mat4x4f_t second)
{
    vec4f_t c1 = MAT4x4_COLUMN1(second);
    vec4f_t c2 = MAT4x4_COLUMN2(second);
    vec4f_t c3 = MAT4x4_COLUMN3(second);
    vec4f_t c4 = MAT4x4_COLUMN4(second);

    vec4f_t sec_c1 = vec4f(second.r1.x, second.r2.x, second.r3.x, second.r4.x); 
    return (mat4x4f_t){
        vec4f(vec4f_sum(vec4f_mul(first.r1, c1)), vec4f_sum(vec4f_mul(first.r1, c2)), vec4f_sum(vec4f_mul(first.r1, c3)), vec4f_sum(vec4f_mul(first.r1, c4))),
        vec4f(vec4f_sum(vec4f_mul(first.r2, c1)), vec4f_sum(vec4f_mul(first.r2, c2)), vec4f_sum(vec4f_mul(first.r2, c3)), vec4f_sum(vec4f_mul(first.r2, c4))),
        vec4f(vec4f_sum(vec4f_mul(first.r3, c1)), vec4f_sum(vec4f_mul(first.r3, c2)), vec4f_sum(vec4f_mul(first.r3, c3)), vec4f_sum(vec4f_mul(first.r3, c4))),
        vec4f(vec4f_sum(vec4f_mul(first.r4, c1)), vec4f_sum(vec4f_mul(first.r4, c2)), vec4f_sum(vec4f_mul(first.r4, c3)), vec4f_sum(vec4f_mul(first.r4, c4))),
    };
}

//add functions

vec4f_t vec4f_add(vec4f_t first, vec4f_t second)
{
        return (vec4f_t){
        .x = first.x + second.x,
        .y = first.y + second.y,
        .z = first.z + second.z,
        .w = first.w + second.w,
    };
}

vec3f_t vec3f_add(vec3f_t first, vec3f_t second)
{
    return (vec3f_t){
        .x = first.x + second.x,
        .y = first.y + second.y,
        .z = first.z + second.z,
    };
};

vec2f_t vec2f_add(vec2f_t first, vec2f_t second)
{
    return (vec2f_t){
        .x = first.x + second.x,
        .y = first.y + second.y,
    };
};

mat4x4f_t mat4x4f_add(mat4x4f_t first, mat4x4f_t second)
{
    return (mat4x4f_t){
        .r1 = vec4f_add(first.r1, second.r1),
        .r2 = vec4f_add(first.r2, second.r2),
        .r3 = vec4f_add(first.r3, second.r3),
        .r4 = vec4f_add(first.r4, second.r4),
    };
}