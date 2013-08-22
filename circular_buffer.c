#include <string.h>
#include <assert.h>
#include <stdio.h>

#include "circular_buffer.h"

void cb_init(cb_t *cb, size_t capacity, free_fn_t data_free)
{
	assert(cb);
	assert(capacity > 0);

	memset(cb, 0, sizeof(cb_t));
	cb->buffer = malloc(capacity * sizeof(void*));
	if (!cb->buffer) {
		return;
	}
	cb->data_free = data_free;
	cb->capacity = capacity;
}

void cb_destroy(cb_t *cb) 
{
	assert(cb);
	assert(cb->buffer);

	if (cb->data_free) {
		while(cb->size > 0) {
			cb->data_free(cb->buffer[cb->tail]);
			cb->tail++;
			if (cb->tail == cb->capacity) {
				cb->tail = 0;	
			}
			cb->size--;
		}
	}
	free(cb->buffer);
	cb->buffer = NULL;
	cb->capacity = 0;
}

void *cb_push(cb_t *cb, void *data)
{
	assert(cb);
	assert(data);

	if (cb->size == cb->capacity) {
		return NULL;
	}
	cb->buffer[cb->head] = data;
	cb->head++;
	if (cb->head == cb->capacity) {
		cb->head = 0;
	}
	cb->size++;
	return data;
}

void *cb_pop(cb_t *cb)
{
	assert(cb);

	void *data;
	if (cb->size == 0)
		return NULL;
	data = cb->buffer[cb->tail];
	cb->tail++;
	if (cb->tail == cb->capacity) {
		cb->tail = 0;
	}
	cb->size--;
	return data;
}
