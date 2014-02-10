#ifndef __GTTHREAD_QUEUE_H
#define __GTTHREAD_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <ucontext.h>
#include <errno.h>
#include <assert.h>

/* Typedef for defining a gtthread_t structure */
typedef unsigned long int gtthread_t;

/* Queue structure */
struct node
{
    gtthread_t data;	// Thread ID
    ucontext_t context;
    struct node * next;
    int active;			// Indicates whether a thread is running or killed
    void * ret;			// Stores return value
};

extern struct node * front;
extern struct node * rear;
extern struct node * current;

/* Pushes thread at the end of the queue, pointed by rear */
extern void push(gtthread_t data, ucontext_t context);

/* Pops thread from the front of the queue, pointed by front */
extern void pop(gtthread_t data);

/* Display the thread queue */
extern void display();

/* Set currently executing thread */
extern void setCurrentThread(struct node * temp);

/* Get currently executing thread context */
//ucontext_t getNextContext(struct node ** front, struct node ** rear, struct node ** current);

#endif // __QUEUE_H
