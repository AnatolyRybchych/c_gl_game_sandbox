#include "../../../include/scenes/game_scene/game_scene.h"



static void init()
{
    load_textures_game_scene();
    init_tiles();
    init_player();
    map.init();
};

static void handle_activity(RenderContext *context)
{
    InputEvent* input;
    while (input = new_event())
    {
        input->disposable.dispose(input); 
    } 
    Player.handle_activity(context);
}

static void render(RenderContext *context)
{
    float scene_width =  context->window_params->size.width/context->window_params->size.height;
    gl_camera.push_state();
        gl_camera.push_state();
            gl_camera.translate2f(vec2f_mul(vec2f(Player.x, Player.y), vec2f(-1, -1)));
            gl_camera.scalef(MAP_SCALE);
            map.draw();
        gl_camera.pop_state();


        Player.scale = SLIME_SCALE;
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