/* GTThreads Mutexes C Source File */
#include "gtthread_mutex.h"

int gtthread_mutex_init(gtthread_mutex_t * mutex)
{
	int result = 0;
	gtthread_mutex_t gmt;

	if(mutex == NULL)
	{
		return ERR;
	}

	gmt = (gtthread_mutex_t) malloc (sizeof(gtthread_mutex_t));
	if(gmt == NULL)
	{
		result = ERR;
	}
	else
	{
		gmt->lock = 0; // Initialize mutex lock in unlocked state
	}

	(* mutex) = gmt;

	return result;

}

int gtthread_mutex_lock(gtthread_mutex_t * mutex)
{
	int result = 0;
	gtthread_mutex_t gmt;
	gtthread_t thread;
	thread = gtthread_self();

	if(mutex == NULL)
	{
		return ERR;
	}

	gmt = mutex;

	if(gmt->lock != 0)
	{
		/* Test and spin */
		while(gmt->lock != 0)
		{
			if(gmt->lock == 0)	// Mutex is unlocked by locking thread
			{
				result = 0;
				break;
			}
		}
		gmt->owner = thread;
		gmt->lock = 1;
	}
	else
	{
		gmt->owner = thread;
		gmt->lock = 1;
	}

	return result;

}

int gtthread_mutex_unlock(gtthread_mutex_t * mutex)
{
	int result = 0;
	gtthread_mutex_t gmt;
	gtthread_t thread;
	thread = gtthread_self();

	if(mutex == NULL)
	{
		return ERR;
	}

	gmt = mutex;

	if(gmt->lock != 0)
	{
		if(gmt->owner == thread)	// Locked mutex is owned by current unlocking thread
		{
			gmt->lock = 0;
			gmt->owner = NULL;
			result = 0;
		}
		else
		{
			result = ERR;	// Unauthorized mutex unlock is detected
		}
	}
	else
	{
		result = ERR;	// Trying to unlock an already unlocked mutex
	}

	return result;

}
