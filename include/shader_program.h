#ifndef __SHADER_PROGRAM_H_
#define __SHADER_PROGRAM_H_

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<glad/glad.h>

GLuint compile_shader(char* source, GLenum shaderType);
GLuint link_shader_program(GLuint vertex, GLuint fragment);

//allocs string, and fills by data from file
char *read_all_file(const char* fileName);


#endif