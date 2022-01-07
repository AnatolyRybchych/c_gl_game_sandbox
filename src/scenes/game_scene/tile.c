#include "../../../include/scenes/game_scene/tile.h"

#define QUAD_VERTICES 6
#define QUAD_MESH_VOLUME 3

static GLuint quad_vbo, *quad_vbo_ptr = NULL;
static const float quad_vert_arr[QUAD_MESH_VOLUME * QUAD_VERTICES] = {
    -1, -1, 0,
    -1,  1, 0,
     1, -1, 0,

     1,  1, 0,
    -1,  1, 0,
     1, -1, 0
};

static void default_tile_draw_proc(Drawable *self)
{
    Tile *tile = (Tile*)self;

    glUseProgram(tile->shader_program);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tile->texture);

    glUniform1i(glGetUniformLocation(tile->shader_program, "tex1"), 0);
    gl_camera.uniform(glGetUniformLocation(tile->shader_program, "MVP"));

    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glVertexPointer(3, GL_FLOAT, 0, NULL);

    glDrawArrays(GL_TRIANGLES, 0, QUAD_VERTICES);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisableClientState(GL_VERTEX_ARRAY);
    glUseProgram(0);
}

static void default_tile_draw_init(Drawable *self)
{
    if(!quad_vbo_ptr){
        glGenBuffers(1, &quad_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
        glBufferData(GL_ARRAY_BUFFER, QUAD_MESH_VOLUME * QUAD_VERTICES * sizeof(float), quad_vert_arr, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        quad_vbo_ptr = &quad_vbo;
    }

    Tile *tile = (Tile*)self;

    tile->drawable.draw = default_tile_draw_proc;
    tile->drawable.draw(self);
}

static void default_tile_clear(void *self)
{
}

Tile new_tile(GLuint texture, GLuint shader_program)
{
    return (Tile){
        .drawable = {
            .draw = default_tile_draw_init,
        },
        .disposable = {
            .dispose = default_tile_clear,
        },
        .texture = texture,
        .shader_program = shader_program,
    };
}