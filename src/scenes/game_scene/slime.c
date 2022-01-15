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


enum VISIBLE_TILES
{
    VISION_LEFT,
    VISION_RIGHT,
    VISION_BOTTOM,
    VISION_TOP,
    VISION_2LEFT,
    VISION_2RIGHT,

    VISIBLE_TILES_COUNT,
};


Tile * Vision[VISIBLE_TILES_COUNT];
static float PosXOnMap;;
static float PosYOnMap;

static void update_vision()
{
    Vision[VISION_LEFT]    = map.getTile(PosXOnMap - 1, PosYOnMap);
    Vision[VISION_RIGHT]   = map.getTile(PosXOnMap + 1, PosYOnMap);
    Vision[VISION_2LEFT]   = map.getTile(PosXOnMap - 2, PosYOnMap);
    Vision[VISION_2RIGHT]  = map.getTile(PosXOnMap + 2, PosYOnMap);

    Vision[VISION_BOTTOM]  = map.getTile(PosXOnMap, PosYOnMap - 1);
    Vision[VISION_TOP]     = map.getTile(PosXOnMap, PosYOnMap + 1);
}

static void update_params()
{
    PosXOnMap = Player.x * 0.5f / BLOCK_SCALE;
    PosYOnMap = Player.y * 0.5f / BLOCK_SCALE;
    update_vision();
}

static void handle_moving(float ftime)
{
    static float acceleration = 0;

    if(!Vision[VISION_BOTTOM])
    {
        acceleration += ftime * 0.1;
        Player.y -= ftime  + acceleration;
    }
    else
    {
        acceleration = 0;
    }

    if(Vision[VISION_LEFT] && Vision[VISION_RIGHT])
    {
        Player.y += ftime;
    }
    

    if(keys_status[GLFW_KEY_A] && !Vision[VISION_LEFT]){
        Player.x -= ftime;
    }
    if(keys_status[GLFW_KEY_D] && !Vision[VISION_RIGHT]){
        Player.x += ftime;
    }
}

static void handle_moving_animation(float ftime)
{
    if((keys_status[GLFW_KEY_A] || keys_status[GLFW_KEY_D]) && !(keys_status[GLFW_KEY_A] && keys_status[GLFW_KEY_D]))
    {
        Player.breath_speed = DEFAULT_SLIME_BREATH_SPEED * 4;
    }
    else
    {
        Player.breath_speed = DEFAULT_SLIME_BREATH_SPEED;
    }
}

static void handle_collision_deformation(float ftime)
{
    if(Vision[VISION_LEFT] || Vision[VISION_2LEFT])
    {
        Player.collision_left = fabs(PosXOnMap - (int)PosXOnMap) +  (Vision[VISION_LEFT]?1:0);
    }
    else
    {
        Player.collision_left = 0;
    }

    if(Vision[VISION_RIGHT] || Vision[VISION_2RIGHT])
    {
        Player.collision_right = fabs((int)PosXOnMap - PosXOnMap) +  (Vision[VISION_RIGHT]?1:0);
    }
    else
    {
        Player.collision_right = 0;
    }
    
}

static void slime_handle_activity(RenderContext *context)
{
    update_params();
    handle_moving(context->ftime);
    handle_moving_animation(context->ftime);
    handle_collision_deformation(context->ftime);
}

static void draw_player(Drawable *self)
{
    Slime *slime = (Slime*)self;
    gl_camera.push_state();
    gl_camera.translate2f(vec2f( 0  , ((SLIME_SIZE_BLOCKS / 2.0) + 1) *BLOCK_SCALE));
    gl_camera.scalef(slime->scale * SLIME_OVERSIZE);

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
        .handle_activity = slime_handle_activity,
        .y = 0,
    };
}