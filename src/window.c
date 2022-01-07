#include "../include/window.h"

WindowParameters WindowParams = {
    .size = {
        .height = DEFAULT_WINDOW_HEIGHT,
        .width = DEFAULT_WINDOW_WIDTH,
    },
};

RenderContext RenderCtx = {
    .window_params = &WindowParams,
};

static void (*on_frame)(RenderContext *context);


int init_window(void (*on_frame_proc)(RenderContext *context))
{
    on_frame = on_frame_proc;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_SAMPLES, 4);

    WindowParams.window = glfwCreateWindow(DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT, DEFAULT_WINDOW_TITLE, NULL, NULL);
    if (!WindowParams.window) return 0;

    glfwMakeContextCurrent(WindowParams.window);

    glfwSetWindowSizeCallback(WindowParams.window, window_size_callback);
    glfwSetKeyCallback(WindowParams.window, key_callback);
    return 1;
}

void start_main_loop()
{
    assert(on_frame);

    while (!glfwWindowShouldClose(WindowParams.window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.3, 0.3, 0.3, 1);
        
        gl_camera.push_state();
        gl_camera.scale2f(vec2f( WindowParams.size.height/ WindowParams.size.width, 1));
        on_frame(&RenderCtx);
        gl_camera.pop_state();

        glfwSwapBuffers(WindowParams.window);
        
        glfwPollEvents();
    }
}

void window_size_callback(GLFWwindow* window, int width, int height)
{
    WindowParams.size.width = width;
    WindowParams.size.height = height;
    glViewport(0,0,width,height);
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    switch (action)
    {
        case GLFW_PRESS:{
            KeyDown key_down_event = {
                .event.type = INPUT_KEY_DOWN,
                .key = key,
                .scan_code = scancode,
                .was_down = keys_status[scancode],
            };
            alloc_input_event((InputEvent*)&key_down_event, INPUT_KEY_DOWN);
            keys_status[key] = 1;
        } break;
        case GLFW_REPEAT:{
            KeyDown key_down_event = {
                .event.type = INPUT_KEY_DOWN,
                .key = key,
                .scan_code = scancode,
                .was_down = keys_status[key],
            };
            alloc_input_event((InputEvent*)&key_down_event, INPUT_KEY_DOWN);
            keys_status[key] = 1;
        } break;
        case GLFW_RELEASE:{
            KeyUp key_up_event = {
                .event.type = INPUT_KEY_UP,
                .key = key,
                .scan_code = scancode,
                .was_down =  keys_status[key],
            };
            alloc_input_event((InputEvent*)&key_up_event, INPUT_KEY_UP);
            keys_status[key] = 0;
        } break;
        default:{
            InputEvent undefined = {
                .type = INPUT_UNDEFINED,
            };
            alloc_input_event(&undefined, INPUT_KEY_UP);
        } break;
    }
}

