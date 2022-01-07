#ifndef __SHADERS_H_
#define __SHADERS_H_

#include <glad/glad.h>
#include "shader_program.h"

typedef enum __SHADER_T Shader;
typedef enum SHADER_PROGRAM_T ShaderProgram;
typedef struct __SHADER_SOURCE_T ShaderSource;
typedef struct __SHADER_PROGRAM_SOURCE_T ShaderProgramSource;

enum __SHADER_T
{
    DEFAULT_VERTEX,
    DEFAULT_FRAGMENT,

    SLIME_VERTEX,
    SLIME_FRAGMENT,

    SHADERS_COUNT,
};

enum SHADER_PROGRAM_T
{
    DEFAULT_SHADER_PROGRAM,
    SLIME_SHADER_PROGRAM,

    SHADER_PROGRAMS_COUNT,
};



struct __SHADER_SOURCE_T
{
    char *file;
    GLenum ShaderType;
};

struct __SHADER_PROGRAM_SOURCE_T
{
    Shader fragment;
    Shader vertex;
};

extern GLuint Shaders[SHADERS_COUNT];
extern ShaderSource ShaderSources[SHADERS_COUNT];

extern GLuint ShaderPrograms[SHADER_PROGRAMS_COUNT];
extern ShaderProgramSource ShaderProgramSources[SHADER_PROGRAMS_COUNT];


void init_shaders();
void link_shader_programs();


#endif