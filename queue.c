#include <stdio.h>
#include <stdlib.h>
#include <ucontext.h>
#include "gtthread.h"
#include "queue.h"

struct node * front = NULL;
struct node * rear = NULL;
struct node * current = NULL;

/* Pushes thread at the end of the queue, pointed by rear */
void push(gtthread_t * data, ucontext_t context)
{
	struct node * temp;
	temp = (struct node *) malloc(sizeof(struct node));

	/* Create node for current thread */
	if(temp == NULL)
	{
		printf("Insufficient memory for thread queue. Exiting program...");
		exit(-1);
	}
	temp->data = * data;
	temp->context = context;
	temp->next = NULL;
	if(front == NULL)	// Queue is empty
	{
		front = temp;
		rear = temp;
	}
	else
	{
		rear->next = temp;
		rear = temp;
	}
}

/* Remove canceled or exited threads from the queue */
void pop(gtthread_t * data)
{
	struct node * temp;
	temp = (struct node *) malloc(sizeof(struct node));
	if(front == rear && rear == NULL)	// Queue is empty
	{
		/* No more threads remain to be scheduled. Exit to main. */
		printf("All philosophers have finished eating. Exiting...");
		free(temp);
		exit(0);
	}

	/* Search for thread specified by data */
	temp = front;
	if(temp->data.gt == data->gt)	// Thread to be deleted is at the front of the queue
	{
		front = temp->next;
	}
	else
	{
		while(temp->next != NULL)
		{
			if(temp->next->data.gt == data->gt)
			{
				temp->next = temp->next->next;
			}
		}
	}
	free(temp);
}

/* Set currently executing thread */
void setCurrentThread(ucontext_t context)
{
	struct node * temp;
	if(front == rear && rear == NULL)	// Queue is empty
	{
		/* No more threads remain to be scheduled. Exit to main. */
		exit(-1);
	}

	/* Search for thread to be set as current */
	current = NULL;
	temp = front;
	while(temp != NULL)
	{
		/*
		if(temp->context == context)
		{
			current = temp;
		}
		*/
		temp = temp->next;
	}
}

/* Get currently executing thread */
ucontext_t getCurrentThread()
{
	ucontext_t context;
	if(current != NULL)
	{
		context = current->context;
	}
	return context;
}
