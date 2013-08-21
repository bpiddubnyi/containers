#ifndef __LIST_H__
#define __LIST_H__

#include <stdlib.h>

typedef struct node node_t;
typedef struct list list_t;

struct node {
	node_t *prev;
	node_t *next;
	void *data;
};

struct list {
	size_t size;
	node_t *head;
	node_t *tail;
};

void list_push_front(list_t *list, node_t *node);
void list_push_back(list_t *list, node_t *node);
node_t* list_pop_front(list_t *list);
node_t* list_pop_back(list_t *list);

#endif /* __LIST_H__ */
