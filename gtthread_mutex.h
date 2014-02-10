/* GTThreads Mutexes C Header File */
#ifndef __GTTHREAD_MUTEX_H
#define __GTTHREAD_MUTEX_H

#include "gtthread_sched.h"

#define ERR 1

struct gtthread_mutex_t{
	int lock;
	gtthread_t owner;
};

typedef struct gtthread_mutex_t * gtthread_mutex_t;

extern int gtthread_mutex_init(gtthread_mutex_t * mutex);
extern int gtthread_mutex_lock(gtthread_mutex_t * mutex);
extern int gtthread_mutex_unlock(gtthread_mutex_t * mutex);

#endif
