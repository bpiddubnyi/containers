#ifndef __CIRCULAR_BUFFER_H__
#define __CIRCULAR_BUFFER_H__

#include <stdlib.h>

typedef void (*free_fn_t)(void*);

typedef struct circular_buffer {
	size_t size;
	size_t capacity;
	void **buffer;
	size_t head;
	size_t tail;
	free_fn_t data_free;
} cb_t;

void cb_init(cb_t *cb, size_t capacity, free_fn_t data_free);
void cb_destroy(cb_t *cb); 
void *cb_push(cb_t *cb, void *data);
void *cb_pop(cb_t *cb);

#endif /* __CIRCULAR_BUFFER_H__ */
