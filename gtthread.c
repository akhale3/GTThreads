/*
 * C file for defining gtthread APIs.
 */
#include <stdio.h>
#include <sys/time.h>
#include <signal.h>
#include <ucontext.h>
#include "gtthread.h"
#include "queue.h"
#define MEM 64000

/* Global variables */

/*
 * TODO: create a global queue which stores all the list of created threads...
 * and create "Current_thread" a pointer to currently executing thread or context...
 * Implemented in queue.c
 */

/*
 * Test itimer upon SIGVTALRM
 */
void testTimer(int signum)
{
	static int count = 0;
	count++;
	printf("Timer expiration count: %d\n", count);
}

/*
 * TODO: Signal handler for SIGVTALRM
 * Swap the context with the thread next to the "Current_thread" in the queue and
 * point the "Current_thread" to the next thread...
 * If it was the last thread in the queue, then execute the main function
 * once and then again start from the first thread in the queue and continue
 * this until all threads have finished their execution
 * when there are no more threads in the queue... just stop the
 * timer and execute the main function until it completes...
 */
void schedule()
{

}

/*
 * Specify preemption period in microseconds. Mandatory first function call.
 * TODO:	Create timer for time = period using setitimer(2).
 *			Initiate context switching.
 */
void gtthread_init(long period)
{
	struct itimerval it_val;	// For setting itimer
	struct sigaction sa;		// For taking an action on receiving SIGVTALRM

	/* Set signal handler to initiate context switch upon receiving SIGVTALRM */
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler = &schedule;
	sigaction(SIGVTALRM, &sa, NULL);

	/* Set timer for time in microseconds indicated by period */
	it_val.it_value.tv_sec = 0;
	it_val.it_value.tv_usec = period;

	/* Set timer expiration interval for the same period */
	it_val.it_interval.tv_sec = 0;
	it_val.it_value.tv_usec = period;

	/* Start virtual timer for calling process */
	setitimer(ITIMER_VIRTUAL, &it_val, NULL);
}

/*
 * Initialize the context using getcontext(), attach a function
 * using makecontext() and keep this in the ready_queue
 * If this was the first thread that is created, then start the timer....
 * Important: block all the signals while adding a new thread to the queue...
 * and after adding it, just unblock all the signals that were previously blocked...
 */
int  gtthread_create(gtthread_t *thread,
                     void *(*start_routine)(void *),
                     void *arg)
{
	ucontext_t currentContext, targetContext;
	getcontext(&currentContext);
	getcontext(&targetContext);
	targetContext.uc_link=0;
	targetContext.uc_stack.ss_sp=malloc(MEM);
	targetContext.uc_stack.ss_size=MEM;
	targetContext.uc_stack.ss_flags=0;
	push(thread, targetContext);
	makecontext(&targetContext, (void *) start_routine, 0);
	swapcontext(&currentContext, &targetContext);
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

/*
 * When the currently executing thread has finished its execution before
 * the context switch, then this function should be executed...
 * The main task is to remove the thread from the ready queue (of course you
 * have to block all the signals and then unblock at last..) and at last it
 * should call the schedule function.
 */
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
