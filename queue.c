/*
 * =====================================================================================
 *
 *       Filename:  queue.c
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/10/19 15:24:48
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  cyher (), cyher.net A~T gmail.com
 *        Company:  cyher.net
 *
 * =====================================================================================
 */
#include "queue.h"
int count = 0;

struct queue *init_queue(void)
{
	struct queue *q = (struct queue *)malloc(sizeof(struct queue));
	q->front = q->rear = (struct node*)malloc(sizeof(struct node));
	q->front->next = NULL;
	return q;
}

int is_queue_empty(struct queue *q)
{
	return q->front == q->rear;
}

void enqueue(struct queue *q, struct path *ch)
{
	struct node *cur= (struct node *)malloc(sizeof(struct node));
	cur->data = ch;
	cur->next=NULL;

	q->rear->next=cur;
	q->rear=cur;

	count++;
}

struct path *dequeue(struct queue *q)
{
	struct path *ch = q->front->next->data;

	if(q->front->next == q->rear) {
		q->rear = q->front;
		free(q->front->next);
		q->front->next=NULL;
	} else {
		struct node *t = q->front->next;
		q->front->next = t->next;
		free(t);
	}

	count--;

	return ch;
}

void reset_queue(struct queue *q)
{
	struct node* head = q->front->next;
	q->front->next = NULL;
	q->rear = q->front;
	struct node *t;

	while(head) {
		t=head->next;
		free(head);
		head=t;
	}
}

void destroy_queue(struct queue *q)
{
	reset_queue(q);
	free(q->front);
	free(q);
}
