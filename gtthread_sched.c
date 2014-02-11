/* GTThread Scheduler C Source File */
#include "gtthread_sched.h"

/* Variable declarations */
struct node * temp;
long gt_period;

/* Initializes virtual time */
void initVirtualTime(long period)
{
	/* Set gt_period */
	gt_period = period;

	/* Set signal handler to initiate  context switch upon receiving SIGVTALRM */
	memset(&sa, 0, sizeof(sa));
	sa.sa_handler =  schedule;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;

	sigemptyset(&sig);
	sigaddset(&sig,SIGVTALRM);

	/* Set timer expiration interval for the same period */
	it_val.it_interval.tv_sec = 0;
	it_val.it_interval.tv_usec = period;

	/* Set timer for time in microseconds indicated by period */
	it_val.it_value.tv_sec = 0;
	it_val.it_value.tv_usec = period;\

	/* Set scheduler context */
	if(!getcontext(&schedulerContext))
	{
		setSchedulerContext();
	}

	sigaction(SIGVTALRM, &sa, NULL);
	setitimer(ITIMER_VIRTUAL, &it_val, NULL);
}

/* Block SIGVTALRM */
void blockSignal()
{
	sigprocmask(SIG_BLOCK, &sig, NULL);
}

/* Unblock SIGVTALRM */
void unblockSignal()
{
	sigprocmask(SIG_UNBLOCK, &sig, NULL);
}

/* Enqueue */
void enqueue(gtthread_t data, ucontext_t context)
{
	/* Block SIGVTALRM for ensuring correct node insertion */
	blockSignal();

	/* Add node to end of queue */
	push(data, context);

	/* Unblock SIGVTALRM */
	unblockSignal();
}

/* Dequeue */
void dequeue(gtthread_t data)
{
	/* Block SIGVTALRM for ensuring correct node insertion */
	blockSignal();

	/* Remove node to end of queue */
	pop(data);

	/* Unblock SIGVTALRM */
	unblockSignal();
}

/* Swaps contexts of running threads */
void schedule(int signal)
{
	blockSignal();

	if(current->active == 1 && front != NULL)
	{
		/* Store current in temporary context */
		temp = current;

		/* Advance current pointer */
		if(current->next != NULL)
		{
			setCurrentThread(current->next);
		}
		else
		{
			setCurrentThread(front);
		}

		/* Reinitialize virtual time and unblock SIGVTALRM */
		initVirtualTime(gt_period);
		unblockSignal();

		/* Swap context */
		swapcontext(&temp->context, &current->context);

	}
	else
	{
		/* Advance current pointer */
		if(current->next != NULL)
		{
			setCurrentThread(current->next);
		}
		else
		{
			setCurrentThread(front);
		}

		/* Reinitialize virtual time and unblock SIGVTALRM */
		initVirtualTime(gt_period);
		unblockSignal();

		/* Swap context */
		swapcontext(&zombie, &current->context);
	}
}

void setSchedulerContext()
{
	schedulerContext.uc_link		   = 0;
	schedulerContext.uc_stack.ss_sp    = malloc(MEM);
	schedulerContext.uc_stack.ss_size  = MEM;
	schedulerContext.uc_stack.ss_flags = 0;
	makecontext(&schedulerContext, (void (*) (void))schedule, 0);
}
