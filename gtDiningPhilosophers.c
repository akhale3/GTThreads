/* Code to implement the dining philosophers problem using gtthread library */

#include "gtthread.h"

#define PHIL 5

gtthread_mutex_t chopstick[PHIL];
gtthread_t philo[PHIL];
int rand_sleep = 0;

void acquireChopstick (int phil, int c, char * hand)
{
	printf ("Philosopher %d tries to acquire %s chopstick %d\n", phil, hand, c);
	gtthread_mutex_lock (&chopstick[c]);
	printf ("Philosopher %d: acquired %s chopstick %d\n", phil, hand, c);
}

void releaseChopsticks (int phil, int left_c, int right_c)
{
	/* Release left chopstick */
	gtthread_mutex_unlock (&chopstick[left_c]);
	printf ("Philosopher %d releases left chopstick %d\n", phil, left_c);

	/* Release right chopstick */
	gtthread_mutex_unlock (&chopstick[right_c]);
	printf ("Philosopher %d releases right chopstick %d\n", phil, right_c);
}

void * philosopher (void * num)
{
	int id;
	int leftChopstick;
	int rightChopstick;

	id = (int)num;
	printf ("Philosopher %d is done thinking and now ready to eat.\n", id);
	rightChopstick = id;
	leftChopstick = id + 1;

	/* Wrap around the chopsticks. */
	if (leftChopstick == PHIL)
		leftChopstick = 0;

	while (1)
	{
		/* Prevent deadlock by first philosopher */
		if (id == 1)
			sleep (rand_sleep);

		acquireChopstick (id, rightChopstick, "right");
		acquireChopstick (id, leftChopstick, "left");

		printf ("Philosopher %d is now eating.\n", id);
		usleep(rand_sleep);
		releaseChopsticks (id, leftChopstick, rightChopstick);
	}

	printf ("Philosopher %d is done eating.\n", id);
	return (NULL);
}

int main4 (int argc, char **argv)
{
	int i;

	/* Initialize a random sleep time between eating and thinking */
	rand_sleep = rand() % 1000;

	/* Initialize mutex lock for chopsticks */
	for (i = 0; i < PHIL; i++)
		gtthread_mutex_init (&chopstick[i]);

	/* Create the specified number of philosopher threads */
	for (i = 0; i < PHIL; i++)
		gtthread_create (&philo[i], philosopher, (void *)(i+1));

	/* Join all philosopher threads */
	for (i = 0; i < PHIL; i++)
		gtthread_join (philo[i], NULL);

	return 0;
}
