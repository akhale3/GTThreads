/* C source file for defining gtthread APIs */
#include "gtthread.h"

/* Global variables */
// Thread
unsigned long thread_id = 0;
ucontext_t targetContext;
int flag = 0;				// Set by first thread

/*
 * Specify preemption period in microseconds. Mandatory first function call.
 */
void gtthread_init(long period)
{
	/* Create a parent node in the queue */
	thread_id++;
	struct node * temp;
	temp = (struct node *) malloc(sizeof(struct node));

	temp->data = thread_id;
	temp->next = NULL;
	temp->active = 1;

	front = temp;
	rear = front;

	/* Set first thread as current thread */
	setCurrentThread(front);

	/* Invoke setVirtualTime function of scheduler */
	initVirtualTime(period);
}

/*
 * Start routine wrapper function.
 */
void gtthread_start(void *(*start_routine)(void *),
					void *arg)
{
	//void * retval = start_routine(arg);
	current->ret = start_routine(arg);
	setcontext(&schedulerContext);
}

/*
 * Create thread context and enqueue.
 */
int gtthread_create(gtthread_t *thread,
                     void *(*start_routine)(void *),
                     void *arg)
{
	/* Set and assign thread ID */
	thread_id++;
	*thread = thread_id;

	/* Set target context */
	getcontext(&targetContext);
	targetContext.uc_link		    = &schedulerContext;
	targetContext.uc_stack.ss_sp    = malloc(MEM);
	targetContext.uc_stack.ss_size  = MEM;
	targetContext.uc_stack.ss_flags = 0;
	makecontext(&targetContext, gtthread_start, 2, start_routine, arg);

	/* Enqueue */
	enqueue(thread_id, targetContext);
	fflush(stdout);

	return 0;
}

int gtthread_join(gtthread_t thread, void **status)
{
	struct node * child;
	child = front;
	while(child->data != thread && child != NULL)
	{
		child = child->next;
	}

	/* Yield calling thread till child becomes inactive */
	while(child->active != 0)
	{
		gtthread_yield();
	}

	if(status != NULL)
	{
		*status = child->ret;
	}

	return 0;
}

void gtthread_exit(void *retval)
{
	current->ret = retval;
	current->active = 0;
	if(front == rear && rear->next == NULL)
	{
		exit(0);
	}
	// TODO: Yield till its child processes finish execution
	dequeue(current->data);
	raise(SIGVTALRM);
}

int gtthread_yield(void)
{
	raise(SIGVTALRM);
	return 0;
}

int gtthread_equal(gtthread_t t1, gtthread_t t2)
{
	if(t1 == t2)
	{
		return 1;	// The two threads are equal
	}
	else
	{
		return 0;	// The two threads are unequal
	}
}

int gtthread_cancel(gtthread_t thread)
{
	struct node * child;
	if(current->data == thread)
	{
		gtthread_exit((void *) GTTHREAD_CANCELLED);
	}
	else
	{
		child = front;
		while(child->data != thread && child != NULL)
		{
			child = child->next;
		}
		child->active = 0;
		child->ret = (void *) GTTHREAD_CANCELLED;
		// TODO: Yield till its child processes finish execution
		dequeue(child->data);
	}
	return 0;
}

gtthread_t gtthread_self(void)
{
	gtthread_t thread_id;
	thread_id = current->data;
	return thread_id;
}
