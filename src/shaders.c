#include "../include/shaders.h"
#ifdef _DEBUG
    #define DEBUG_PARENT "build/out/"
#else
    #define DEBUG_PARENT ""
#endif
#define SHADERS_DIR DEBUG_PARENT"shaders/"

char *get_shader_type_str(GLenum type);

GLuint Shaders[SHADERS_COUNT];
ShaderSource ShaderSources[SHADERS_COUNT] = {
    [DEFAULT_VERTEX]   = {.file = SHADERS_DIR"default_vert.glsl", .ShaderType = GL_VERTEX_SHADER},
    [DEFAULT_FRAGMENT] = {.file = SHADERS_DIR"default_frag.glsl", .ShaderType = GL_FRAGMENT_SHADER},

    [SLIME_VERTEX]   = {.file = SHADERS_DIR"slime_vert.glsl", .ShaderType = GL_VERTEX_SHADER},
    [SLIME_FRAGMENT] = {.file = SHADERS_DIR"slime_frag.glsl", .ShaderType = GL_FRAGMENT_SHADER},
};

GLuint ShaderPrograms[SHADER_PROGRAMS_COUNT];
ShaderProgramSource ShaderProgramSources[SHADER_PROGRAMS_COUNT] = {
    [DEFAULT_SHADER_PROGRAM] = {.vertex = DEFAULT_VERTEX, .fragment = DEFAULT_FRAGMENT},
    [SLIME_SHADER_PROGRAM] = {.vertex = SLIME_VERTEX, .fragment = SLIME_FRAGMENT},
};


void init_shaders()
{
    printf("\nshader initialization{\n");
    for (size_t curr_shader = 0; curr_shader < SHADERS_COUNT; curr_shader++)
    {
        printf("\tShaders[%u] (%s)\t:%s",curr_shader , get_shader_type_str(ShaderSources[curr_shader].ShaderType), ShaderSources[curr_shader].file);

        char *shader_file_data = read_all_file(ShaderSources[curr_shader].file);
        Shaders[curr_shader] = compile_shader(shader_file_data, ShaderSources[curr_shader].ShaderType);
        free(shader_file_data);

        if(Shaders[curr_shader]) 
            printf("\t-> (%u) success;\n", Shaders[curr_shader]);
        else
            printf("\t-> (%u) feiled;\n", Shaders[curr_shader]);
    }
    printf("};\n");
}

void link_shader_programs()
{
    printf("\nshader programs linking{\n");
    for (size_t curr_shader_prog = 0; curr_shader_prog < SHADER_PROGRAMS_COUNT; curr_shader_prog++)
    {
        printf("\tShaderPrograms[%u] {vertex: Shaders[%u], fragment: Shaders[%u]}",curr_shader_prog , ShaderProgramSources[curr_shader_prog].vertex ,ShaderProgramSources[curr_shader_prog].fragment);

        ShaderPrograms[curr_shader_prog] = link_shader_program(Shaders[ShaderProgramSources[curr_shader_prog].vertex] ,Shaders[ShaderProgramSources[curr_shader_prog].fragment]);

        if(ShaderPrograms[curr_shader_prog]) 
            printf("\t-> (%u) success;\n", ShaderPrograms[curr_shader_prog]);
        else
            printf("\t-> (%u) feiled;\n", ShaderPrograms[curr_shader_prog]);
    }
    printf("};\n");
}

char *get_shader_type_str(GLenum type)
{
    switch (type)
    {
    case GL_VERTEX_SHADER:
        return "GL_VERTEX_SHADER";
    case GL_FRAGMENT_SHADER:
        return "GL_FRAGMENT_SHADER";
    case GL_GEOMETRY_SHADER:
        return "GL_GEOMETRY_SHADER";
    default:
        return "SHADER_TYPE_UNKNOWN";
    }
}