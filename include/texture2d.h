#ifndef __TEXTURE2D_H_
#define __TEXTURE2D_H_

#include <glad/glad.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct 
{
    int width, height;
} SIZE;

//img_size can be NULL
//bytes_per_pixel can be NULL
GLuint load_texture2d(char *file, SIZE *img_size, int *bytes_per_pixel);

GLuint load_texture2d_from_array(void *data, int width, int height, int bytes_per_pixel);

void * read_bmp_file(const char *fileName, SIZE *size, int *bytesPerPixel);


void load_textures(const char *const *texture_sources, GLuint *textures, int count);

#endif