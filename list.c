#include <assert.h>

#include "list.h"

void list_push_front(list_t *list, node_t *node)
{
	assert(list);
	assert(node);

	node->next = list->head;
	if (list->head) {
		list->head->prev = node;
	} else {
		list->tail = node;
	}
	list->head = node;

	list->size++;
}

void list_push_back(list_t *list, node_t *node)
{
	assert(list);
	assert(node);

	node->prev = list->tail;
	if (list->tail) {
		list->tail->next = node;
	} else {
		list->head = node;
	}
	list->tail = node;

	list->size++;
}

node_t* list_pop_front(list_t *list)
{
	assert(list);

	node_t *result = list->head;
	if (result) {
		list->size--;
		list->head = list->head->next;
		if (list->head) {
			list->head->prev = NULL;
		} else {
			list->tail = NULL;	
		}
		result->next = NULL;
	}

	return result;
}

node_t* list_pop_back(list_t *list)
{
	assert(list);

	node_t *result = list->tail;
	if (result) {
		list->size--;
		list->tail = list->tail->prev;
		if (list->tail) {
			list->tail->next = NULL;
		} else {
			list->head = NULL;
		}
		result->prev = NULL;
	}

	return result;
}
