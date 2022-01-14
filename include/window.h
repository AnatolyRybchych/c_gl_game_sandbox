#ifndef __WINDOW_H_
#define __WINDOW_H_

#include<stdio.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

#include "handle_queue.h"
#include "../include/gl_camera.h"

#define DEFAULT_WINDOW_TITLE "Window"
#define DEFAULT_WINDOW_WIDTH 800
#define DEFAULT_WINDOW_HEIGHT 600

typedef struct __SIZEF_T Sizef;
typedef struct __WINDOW_PARAMETERS_T WindowParameters;
typedef struct __RENDER_CONTEXT_T RenderContext;

int init_window(void (*on_frame_proc)(RenderContext *context));
void window_size_callback(GLFWwindow* window, int width, int height);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
void start_main_loop();


extern WindowParameters WindowParams;


struct __RENDER_CONTEXT_T{
    WindowParameters *window_params;
    double ftime;
    double time;
};

struct __SIZEF_T{
    float width;
    float height;
};

struct __WINDOW_PARAMETERS_T{
    Sizef size;
    GLFWwindow *window;
};

#endif