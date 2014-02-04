#ifndef __QUEUE_H
#define __QUEUE_H
#include "gtthread.h"
#include <ucontext.h>

/* Queue structure */
struct node
{
    gtthread_t data;
    ucontext_t context;
    struct node * next;
}*front, *rear, *current;

/* Pushes thread at the end of the queue, pointed by rear */
void push(gtthread_t * data, ucontext_t context);

/* Pops thread from the front of the queue, pointed by front */
void pop(gtthread_t * data);

/* Set currently executing thread */
void setCurrentThread(ucontext_t context);

/* Get currently executing thread */
ucontext_t getCurrentThread();

#endif // __QUEUE_H
