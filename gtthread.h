#ifndef __GTTHREAD_H
#define __GTTHREAD_H

#include "gtthread_mutex.h"

#define MEM 64000
#define GTTHREAD_CANCELLED "GTTHREAD_CANCELLED"

/* Must be called before any of the below functions. Failure to do so may
 * result in undefined behavior. 'period' is the scheduling quantum (interval)
 * in microseconds (i.e., 1/1000000 sec.). */
extern void gtthread_init(long period);

/* see man pthread_create(3); the attr parameter is omitted, and this should
 * behave as if attr was NULL (i.e., default attributes) */
extern int  gtthread_create(gtthread_t *thread,
                     void *(*start_routine)(void *),
                     void *arg);

/* see man pthread_join(3) */
extern int  gtthread_join(gtthread_t thread, void **status);

/* gtthread_detach() does not need to be implemented; all threads should be
 * joinable */

/* see man pthread_exit(3) */
extern void gtthread_exit(void *retval);

/* see man sched_yield(2) */
extern int gtthread_yield(void);

/* see man pthread_equal(3) */
extern int  gtthread_equal(gtthread_t t1, gtthread_t t2);

/* see man pthread_cancel(3); but deferred cancelation does not need to be
 * implemented; all threads are canceled immediately */
extern int  gtthread_cancel(gtthread_t thread);

/* see man pthread_self(3) */
extern gtthread_t gtthread_self(void);


/* see man pthread_mutex(3); except init does not have the mutexattr parameter,
 * and should behave as if mutexattr is NULL (i.e., default attributes); also,
 * static initializers do not need to be implemented */
//int  gtthread_mutex_init(gtthread_mutex_t *mutex);
//int  gtthread_mutex_lock(gtthread_mutex_t *mutex);
//int  gtthread_mutex_unlock(gtthread_mutex_t *mutex);

/* gtthread_mutex_destroy() and gtthread_mutex_trylock() do not need to be
 * implemented */

#endif // __GTTHREAD_H
