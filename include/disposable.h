#ifndef __DISPOSABLE_H_
#define __DISPOSABLE_H_

typedef struct __DISPOSABLE_T Disposable;

struct __DISPOSABLE_T
{
    //self -> pointer to child of disposable
    void (*dispose)(void *self);
};

#endif