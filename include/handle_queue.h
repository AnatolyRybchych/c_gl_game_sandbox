#ifndef _HANDLE_QUEUE_H_
#define _HANDLE_QUEUE_H_

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "disposable.h"

#ifndef EVENT_QUEUE_SIZE
    #define EVENT_QUEUE_SIZE 1000
#endif

typedef enum   __INPUT_TYPE_T InputType;

typedef struct __INPUT_EVENT_T InputEvent; 
    //childs
    typedef struct __MOUSE_MOVE_INPUT_EVENT_T MouseMove;
    typedef struct __MOUSE_DOWN_INPUT_EVENT_T MouseDown;
    typedef struct __MOUSE_UP_INPUT_EVENT_T MouseUp;
    typedef struct __KEY_UP_INPUT_EVENT_T KeyUp;
    typedef struct __KEY_DOWN_INPUT_EVENT_T KeyDown;

//event will copied
void alloc_input_event(InputEvent *event, InputType type);

InputEvent *new_event();

extern unsigned char keys_status[65535];

enum __INPUT_TYPE_T
{
    INPUT_MOUSE_MOVE,
    INPUT_MOUSE_DOWN,
    INPUT_MOUSE_UP,

    INPUT_KEY_DOWN,
    INPUT_KEY_UP,

    INPUT_UNDEFINED,
};

struct __INPUT_EVENT_T
{
    InputType type;
    Disposable disposable;
};

struct __MOUSE_MOVE_INPUT_EVENT_T
{
    //Should be in top
    InputEvent event;
    //////////////////
    double x_pos;
    double y_pos;

    int is_ldown;
    int is_rdown;
};

struct __MOUSE_DOWN_INPUT_EVENT_T
{
    //Should be in top
    InputEvent event;
    //////////////////
    double x_pos;
    double y_pos;
};

struct __MOUSE_UP_INPUT_EVENT_T
{
    //Should be in top
    InputEvent event;
    //////////////////
    double x_pos;
    double y_pos;
};

struct __KEY_UP_INPUT_EVENT_T
{
    //Should be in top
    InputEvent event;
    //////////////////
    int key;
    int scan_code;
    unsigned char was_down;
};

struct __KEY_DOWN_INPUT_EVENT_T
{
    //Should be in top
    InputEvent event;
    //////////////////
    int key;
    int scan_code;
    unsigned char was_down;
};

#endif