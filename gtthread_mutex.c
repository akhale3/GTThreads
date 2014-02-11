/* GTThreads Mutexes C Source File */
#include "gtthread_mutex.h"

int mutexID = 0;

int gtthread_mutex_init(gtthread_mutex_t * mutex)
{
	mutexID++;
	*mutex = mutexID;
	mutexTracker[mutexID] = 1;

	return 0;
}

int gtthread_mutex_lock(gtthread_mutex_t * mutex)
{
	while(mutexTracker[*mutex] != 1)
	{
		raise(SIGVTALRM);
	}
	mutexTracker[*mutex] = current->data;

	return 0;
}

int gtthread_mutex_unlock(gtthread_mutex_t * mutex)
{
	if(mutexTracker[*mutex] == current->data)
	{
		mutexTracker[*mutex] = 1;
		return 0;
	}
	else
	{
		return 1;	// Mutex unlock error
	}

}
