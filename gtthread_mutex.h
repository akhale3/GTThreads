/* GTThreads Mutexes C Header File */
#ifndef __GTTHREAD_MUTEX_H
#define __GTTHREAD_MUTEX_H

#include "gtthread_sched.h"

#define MAX 100000

typedef unsigned long gtthread_mutex_t;
unsigned long mutexTracker[MAX];

extern int gtthread_mutex_init(gtthread_mutex_t * mutex);
extern int gtthread_mutex_lock(gtthread_mutex_t * mutex);
extern int gtthread_mutex_unlock(gtthread_mutex_t * mutex);

#endif
