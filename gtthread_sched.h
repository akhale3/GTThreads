/* GTThread Scheduler C Header File */
#ifndef __GTTHREAD_SCHED_H
#define __GTTHREAD_SCHED_H

#include "gtthread_queue.h"

#define MEM 64000

/* Signaling variables */
sigset_t sig;
struct sigaction sa;

/* Context */
ucontext_t zombie;
ucontext_t schedulerContext;

/* Timer */
struct itimerval it_val;

/* Functions */
extern void initVirtualTime(long period);
extern void blockSignal();
extern void unblockSignal();
extern void enqueue(gtthread_t data, ucontext_t context);
extern void dequeue(gtthread_t data);
extern void schedule(int signal);
extern void setSchedulerContext();

#endif
