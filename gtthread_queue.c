#include "gtthread_queue.h"

struct node * front = NULL;
struct node * rear = NULL;
struct node * current = NULL;

/* Pushes thread at the end of the queue, pointed by rear */
void push(gtthread_t data, ucontext_t context)
{
	struct node * temp;
	temp = (struct node *) malloc(sizeof(struct node));

	temp->data = data;
	temp->context = context;
	temp->next = NULL;
	temp->active = 1;

	if(front == NULL)	// Queue is empty
	{
		front = temp;
		rear = front;
	}
	else
	{
		rear->next = temp;
		rear = temp;
	}
}

/* Remove canceled or exited threads from the queue */
void pop(gtthread_t data)
{
	struct node * temp;

	if(front == rear && rear == NULL)	// Queue is empty
	{
		free(temp);
	}
	else
	{
		/* Search for thread specified by data */
		temp = front;
		if(temp->data == data)	// Thread to be deleted is at the front of the queue
		{
			temp->active = 0;
			front = temp->next;
		}
		else
		{
			while(temp->next != NULL)
			{
				if(temp->next->data == data)
				{
					temp->next->active = 0;
					temp->next = temp->next->next;
					if(temp->next == NULL)
					{
						rear = temp;	// Thread to be deleted is at the rear of the queue
					}
				}
			}
		}
		free(temp);
	}
}

/* Debug routine: Display thread queue */

void display()
{
	struct node * temp;
	if(front == rear && rear == NULL)	// Queue is empty
	{
		printf("Queue underflow");
	}
	temp = front;
	while(temp != NULL)
	{
		printf("Data: %lu\n", (long) temp->data);
		printf("Active: %d\n", (int) temp->active);
		printf("Next: %lu\n", (long) temp->next);
		temp = temp->next;
	}
}


/* Set currently executing thread in round robin fashion */
void setCurrentThread(struct node * temp)
{
	current = temp;
}

/* Deprecated: Delete before submission
 * Get context of thread to switch to */
/*
ucontext_t getNextContext(struct node ** front, struct node ** rear, struct node ** current)
{
	ucontext_t context;
	if(* current != NULL)
	{
		/* If current points to last thread in queue, set to front /

		if(* current == * rear)
		{
			* current = * front;
		}
		else
		{
			(* current) = (* current)->next;
		}

		/* Retrieve context of thread referenced by current /
		context = (* current)->context;
	}
	return context;
}
*/
