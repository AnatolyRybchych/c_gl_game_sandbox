#ifndef __DRAWABLE_H_
#define __DRAWABLE_H_

typedef struct __DRAWABLE_T Drawable;

struct __DRAWABLE_T
{
    void (*draw)(Drawable* self);
};

#endif