#include "../../../include/scenes/game_scene/slime.h"

#define QUAD_VERTICES 6
#define QUAD_MESH_VOLUME 3

Slime Player;

static GLuint quad_vbo, *quad_vbo_ptr = NULL;
static const float quad_vert_arr[QUAD_MESH_VOLUME * QUAD_VERTICES] = {
    -1, -1, 0,
    -1,  1, 0,
     1, -1, 0,

     1,  1, 0,
    -1,  1, 0,
     1, -1, 0
};

static void draw_player(Drawable *self)
{
    Slime *slime = (Slime*)self;
    gl_camera.push_state();
    gl_camera.scalef(slime->scale);

    glUseProgram(slime->shader_program);

    gl_camera.uniform(glGetUniformLocation(slime->shader_program, "MVP"));
    glUniform1f(glGetUniformLocation(slime->shader_program, "time"), glfwGetTime());
    glUniform1f(glGetUniformLocation(slime->shader_program, "breath_speed"), slime->breath_speed);
    glUniform2f(glGetUniformLocation(slime->shader_program, "collision"), slime->collision_right, slime->collision_left);

    glEnableClientState(GL_VERTEX_ARRAY);

    glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
    glVertexPointer(3, GL_FLOAT, 0, NULL);

    glDrawArrays(GL_TRIANGLES, 0, QUAD_VERTICES);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glUseProgram(0);
    gl_camera.pop_state();
}

void init_player()
{
    if(!quad_vbo_ptr){
        glGenBuffers(1, &quad_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, quad_vbo);
        glBufferData(GL_ARRAY_BUFFER, QUAD_MESH_VOLUME * QUAD_VERTICES * sizeof(float), quad_vert_arr, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        quad_vbo_ptr = &quad_vbo;
        printf("\nSlime mesh vbo\t-> (%u) ", quad_vbo);
        if(quad_vbo) printf("success;\n");
        else printf("feiled;\n");
    }

    Player = (Slime){
        .drawable = {
            .draw = draw_player,
        },
        .breath_speed = DEFAULT_SLIME_BREATH_SPEED,
        .shader_program = ShaderPrograms[SLIME_SHADER_PROGRAM],
    };
}