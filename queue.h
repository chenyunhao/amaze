/*
 * =====================================================================================
 *
 *       Filename:  queue.h
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/10/19 15:24:52
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  cyher (), cyher.net A~T gmail.com
 *        Company:  cyher.net
 *
 * =====================================================================================
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include "amaze.h"

struct point {
	int _x;
	int _y;
};

struct node {
	struct path *data;
	struct node *next;
};

struct queue {
	struct node *front;
	struct node *rear;
};

struct queue *init_queue(void);
int is_queue_empty(struct queue *q);
void enqueue(struct queue *q,struct path *ch);
struct path *dequeue(struct queue *q);
void reset_queue(struct queue *q);
void destroy_queue(struct queue *q);
#endif           /* QUEUE_H */
