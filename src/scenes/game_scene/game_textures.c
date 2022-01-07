#include "../../../include/scenes/game_scene/game_textures.h"

GLuint GameSceneTextures[TEXTURES_COUNT];
static const char *TextureSources[TEXTURES_COUNT] = {
    [TEXTURE_DIRT_DEF] = TEXTURES_DIR"def.bmp",
};

void load_textures_game_scene()
{
    load_textures(TextureSources, GameSceneTextures, TEXTURES_COUNT);
}