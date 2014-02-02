/*
 * C file for defining gtthread APIs.
 */
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include "gtthread.h"

/*
 * Specify preemption period in microseconds. Mandatory first function call.
 * TODO:	Create timer for time = period using setitimer(2).
 *			Initiate context switching.
 */
void gtthread_init(long period)
{
	struct itimerval it_val;
}

int  gtthread_create(gtthread_t *thread,
                     void *(*start_routine)(void *),
                     void *arg)
{

}

int  gtthread_join(gtthread_t thread, void **status)
{

}

void gtthread_exit(void *retval)
{

}

int gtthread_yield(void)
{

}

int  gtthread_equal(gtthread_t t1, gtthread_t t2)
{

}

int  gtthread_cancel(gtthread_t thread)
{

}

gtthread_t gtthread_self(void)
{

}

int  gtthread_mutex_init(gtthread_mutex_t *mutex)
{

}

int  gtthread_mutex_lock(gtthread_mutex_t *mutex)
{

}

int  gtthread_mutex_unlock(gtthread_mutex_t *mutex)
{

}
