#include "../include/window.h"
#include "../include/scenes.h"

void error_callback(int error, const char* description);
void exit_error(char* msg);
void on_frame(RenderContext *context);
void init();

Scene *CurrScene;


int main(int argc, char* argv[])
{
    if (!glfwInit()) exit_error("Cannot init glfw");

    glfwSetErrorCallback(error_callback);

    if(!init_window(on_frame)) exit_error("Cannot create window");
    if(!gladLoadGL()) exit_error("Cannot load opengl functions");

    init();

    start_main_loop();

    glfwTerminate();
    return 0;
}

void exit_error(char* msg)
{
    fprintf(stderr,"ERROR:%s\n",msg);
    glfwTerminate();
    exit(EXIT_FAILURE);
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error %d: %s\n", error, description);
}


float angle = 0.0f;
void on_frame(RenderContext *context)
{
    CurrScene->on_frame(context);
}


void init()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    init_shaders();
    link_shader_programs();
    Scenes[SCENE_GAME]->init();
    CurrScene = Scenes[SCENE_GAME];
}