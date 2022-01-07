
#include "../include/shader_program.h"


GLuint compile_shader(char* source, GLenum shaderType)
{
    char info_log[GL_INFO_LOG_LENGTH + 1];

    GLuint shader = glCreateShader(shaderType);

    if(!shader)
    {
        fprintf(stderr, "ERROR:%s\n", "cannot create shader");
    }

    glShaderSource(shader, 1, (const GLchar *const *)&source, NULL);
    
    glCompileShader(shader);

    GLint status;
    glGetShaderiv(shader,GL_COMPILE_STATUS, &status);
    if(!status) 
    {
        glGetShaderInfoLog(shader, GL_INFO_LOG_LENGTH,NULL, info_log);
        fprintf(stderr, "ERROR:%s\n",info_log);
        glDeleteShader(shader);
        return 0;
    }
    else
    {
        return shader;
    }
}

GLuint link_shader_program(GLuint vertex, GLuint fragment)
{
    char info_log[GL_INFO_LOG_LENGTH + 1];

    GLuint ShaderProgram = glCreateProgram();
    if(!ShaderProgram)
    {
        fprintf(stderr, "ERROR:%s\n","cannot create shader programm");
        return 0;
    }

    glAttachShader(ShaderProgram, vertex);
    glAttachShader(ShaderProgram, fragment);
    glLinkProgram(ShaderProgram);

    GLint status;
    glGetProgramiv(ShaderProgram, GL_LINK_STATUS, &status);
    if(!status) 
    {
        glGetProgramInfoLog(ShaderProgram, GL_INFO_LOG_LENGTH,NULL, info_log);
        fprintf(stderr, "ERROR:%s\n",info_log);
        return 0;
    }
    else
    {
        return ShaderProgram;
    }
}

char *read_all_file(const char* fileName)
{
    FILE *file = fopen(fileName,"r");

    fseek(file,0,SEEK_END);
    int size = ftell(file);
    fseek(file,0,SEEK_SET);

    char *data = (char*)malloc(size + 1);
    memset(data, 0, size + 1);

    fread(data,size,1,file);

    fclose(file);
    return data;
}