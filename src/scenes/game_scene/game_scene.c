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
    static vec2f_t player_prev = {0,0};
    vec2f_t player_curr = vec2f(Player.x, Player.y); 
    vec2f_t player_off = vec2f_add(player_prev, vec2f_mul(player_curr, vec2f(-1, -1)));
    player_prev = player_curr;

    float scene_width =  context->window_params->size.width/context->window_params->size.height;
        
    map.translate(player_off);
    map.draw();

    Player.scale = SLIME_SCALE;
    Player.drawable.draw((Drawable*)&Player);
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