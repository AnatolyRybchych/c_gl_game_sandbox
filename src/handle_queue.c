#include "../include/handle_queue.h"

static InputEvent *event_queue[EVENT_QUEUE_SIZE];
static InputEvent **first = event_queue;
static InputEvent **last = event_queue;
static unsigned int events_count = 0; 

unsigned char keys_status[65535] = {0};

static void event_dispose(void *self)
{
    free(self);
}

static InputEvent *alloc_event(InputType type, const InputEvent* src)
{
    InputEvent *res;
    switch (type)
    {
        case INPUT_MOUSE_MOVE:{
            res = malloc(sizeof(MouseMove));
            *(MouseMove*)res = *(MouseMove*)src;
            res->disposable.dispose = event_dispose;
        }break;
        case INPUT_MOUSE_DOWN:{
            res =  malloc(sizeof(MouseDown));
            *(MouseDown*)res = *(MouseDown*)src;
            res->disposable.dispose = event_dispose;
        }break;
        case INPUT_MOUSE_UP:{
            res =  malloc(sizeof(MouseUp));
            *(MouseUp*)res = *(MouseUp*)src;
            res->disposable.dispose = event_dispose;
        }break;
        case INPUT_KEY_DOWN:{
            res =  malloc(sizeof(KeyDown));
            *(KeyDown*)res = *(KeyDown*)src;
            res->disposable.dispose = event_dispose;
        }break;
        case INPUT_KEY_UP:{
            res =  malloc(sizeof(KeyUp));
            *(KeyUp*)res = *(KeyUp*)src;
            res->disposable.dispose = event_dispose;
        }break;
        default:{
            assert(0&&"UNREACHABLE");
            res =  0;
        }break;
    }
    return res;
}

void alloc_input_event(InputEvent *event, InputType type)
{
    if(events_count == EVENT_QUEUE_SIZE)
    {
        fprintf(stderr, "ERROR: event queue owerflow\n");
        return;
    }
    else if(last == event_queue + EVENT_QUEUE_SIZE - 1)
    {
        *last = alloc_event(type, (const InputEvent*)event);
        last = event_queue;
    }
    else
    {
        *last = alloc_event(type, (const InputEvent*)event);
        last ++;
    }
    events_count ++;
}

InputEvent *new_event()
{
    InputEvent* res;
    if(events_count == 0) return 0;
    else if(first == event_queue + EVENT_QUEUE_SIZE -1)
    {
        res = *first;
        first = event_queue;
        events_count--;
    }
    else
    {
        res = *first;
        first ++;
        events_count--;
    }
    if(events_count == 0)
    {
        first = event_queue;
        last = event_queue;
    }
    return res;
}