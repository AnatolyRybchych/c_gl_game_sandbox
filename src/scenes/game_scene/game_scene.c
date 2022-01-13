#include "../../../include/scenes/game_scene/game_scene.h"

#define BLOCK_SCALE 0.06f



static void init()
{
    load_textures_game_scene();
    init_tiles();
    init_player();
};

static void handle_activity(RenderContext *context)
{
    static double time, ftime;
    double t = glfwGetTime();
    ftime = t - time;
    time = t;

    InputEvent* input;
    while (input = new_event())
        input->disposable.dispose(input); 
    
    if(keys_status[GLFW_KEY_A]){
        Player.x -= ftime;
    }
    if(keys_status[GLFW_KEY_D]){
        Player.x += ftime;
    }

    if((keys_status[GLFW_KEY_A] || keys_status[GLFW_KEY_D]) && !(keys_status[GLFW_KEY_A] && keys_status[GLFW_KEY_D]))
    {
        Player.breath_speed = DEFAULT_SLIME_BREATH_SPEED * 4;
    }
    else
    {
        Player.breath_speed = DEFAULT_SLIME_BREATH_SPEED;
    }
    


    if(Player.x < 0)
    {
        Player.x = 0;
    }
    if(Player.x < 1 - Player.scale - 0.1){
        Player.collision_left = (1 - Player.scale - 0.1 - Player.x) * 2;
    }
}

static void render(RenderContext *context)
{
    float scene_width =  context->window_params->size.width/context->window_params->size.height;

    gl_camera.push_state();

    for(float y = 1; y >= -0.6; y-= 2*BLOCK_SCALE)
    {
        gl_camera.push_state();
        gl_camera.translate2f(vec2f(-0.6/2,y));
                gl_camera.scalef(BLOCK_SCALE);
        Tiles[TILE_DIRT]->drawable.draw((Drawable*)Tiles[TILE_DIRT]);
        gl_camera.pop_state();
    }

    for (float y = -0.6; y > -1; y-= 2*BLOCK_SCALE)
    {
        for (float x = - scene_width; x < scene_width; x+= 2*BLOCK_SCALE)
        {
            gl_camera.push_state();
            gl_camera.translate2f(vec2f(x,y));
                    gl_camera.scalef(BLOCK_SCALE);
            Tiles[TILE_DIRT]->drawable.draw((Drawable*)Tiles[TILE_DIRT]);
            gl_camera.pop_state();
        }
    }

    Player.scale = 0.6;
    Player.drawable.draw((Drawable*)&Player);
    gl_camera.pop_state();
}

static void on_frame(RenderContext *context)
{
    handle_activity(context);
    render(context);
}

static void close()
{
    glDeleteTextures(TEXTURES_COUNT, GameSceneTextures);
}

Scene GameScene = {
    .init = init,
    .on_frame = on_frame,
    .close = close,
};