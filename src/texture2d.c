#include "../include/texture2d.h"

#define DATA_OFFSET_OFFSET 0x000A
#define WIDTH_OFFSET 0x0012
#define HEIGHT_OFFSET 0x0016
#define BITS_PER_PIXEL_OFFSET 0x001C
#define HEADER_SIZE 14
#define INFO_HEADER_SIZE 40
#define NO_COMPRESION 0
#define MAX_NUMBER_OF_COLORS 0
#define ALL_COLORS_REQUIRED 0

void * read_bmp_file(const char *fileName, SIZE *size, int *bytesPerPixel)
{
    unsigned char *pixels;
    FILE *imageFile = fopen(fileName, "rb");
    int32_t dataOffset;
    fseek(imageFile, DATA_OFFSET_OFFSET, SEEK_SET);
    fread(&dataOffset, 4, 1, imageFile);
    fseek(imageFile, WIDTH_OFFSET, SEEK_SET);
    fread(&(size->width), 4, 1, imageFile);
    fseek(imageFile, HEIGHT_OFFSET, SEEK_SET);
    fread(&(size->height), 4, 1, imageFile);
    int16_t bitsPerPixel;
    fseek(imageFile, BITS_PER_PIXEL_OFFSET, SEEK_SET);
    fread(&bitsPerPixel, 2, 1, imageFile);
    *bytesPerPixel = ((int32_t)bitsPerPixel) / 8;
 
    int paddedRowSize = (int)(4 * ceil((float)(size->width) / 4.0f))*(*bytesPerPixel);
    int unpaddedRowSize = (size->width)*(*bytesPerPixel);
    int totalSize = unpaddedRowSize*(size->height);
    pixels = (unsigned char*)malloc(totalSize);
    int i = 0;
    unsigned char *currentRowPointer = pixels+((size->height-1)*unpaddedRowSize);
    for (i = 0; i < size->height; i++)
    {
        fseek(imageFile, dataOffset+(i*paddedRowSize), SEEK_SET);
        fread(currentRowPointer, 1, unpaddedRowSize, imageFile);
        currentRowPointer -= unpaddedRowSize;
    }
 
    fclose(imageFile);

    return pixels;
}

GLuint load_texture2d_from_array(void *data, int width, int height, int bytes_per_pixel)
{
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    GLenum input_format;

    assert((bytes_per_pixel == 4 || bytes_per_pixel == 3) && "unimplemented texture input format");
    if(bytes_per_pixel == 4) input_format = GL_BGRA;
    else if(bytes_per_pixel == 3) input_format = GL_BGR;


    glTexImage2D(GL_TEXTURE_2D, 0 , GL_RGBA, width, height, 0, input_format, GL_UNSIGNED_BYTE, data);

    glBindTexture(GL_TEXTURE_2D, 0);

    return texture;
}


GLuint load_texture2d(char *file, SIZE *img_size, int *bytes_per_pixel)
{

    SIZE size;
    int bps;
    void *data = read_bmp_file(file, &size, &bps);

    GLuint texture = load_texture2d_from_array(data, size.width, size.height, bps); 

    if(img_size) *img_size = size;
    if(bytes_per_pixel) *bytes_per_pixel = bps;

    free(data);
    return texture;
}


void load_textures(const char *const *texture_sources, GLuint *textures, int count)
{
    printf("\ntextures initialization{\n");
    for (int curr_tex = 0; curr_tex < count; curr_tex++)
    {
        textures[curr_tex] = load_texture2d((char*)texture_sources[curr_tex], NULL, NULL);

        printf("\tTextures[%i] :%s\t-> (%i) ", curr_tex, texture_sources[curr_tex], textures[curr_tex]);
        if(textures[curr_tex]) printf("success\n");
        else printf("feiled\n");
    }
    printf("};\n");
}