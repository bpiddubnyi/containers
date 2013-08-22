#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <unistd.h>
#include "circular_buffer.h"

#define BUF_CAPACITY 1024 

int main()
{
	cb_t cb;
	int i;
	int *data_buf, *res_buf;

	printf("    cb_init()");
	
	cb_init(&cb, BUF_CAPACITY, NULL);
	assert(cb.buffer);
	
	puts("\tok");

	printf("    cb_push()");
	
	for (i = 0; i < BUF_CAPACITY; ++i) {
		data_buf = malloc(sizeof(int));
		*data_buf = i;
		res_buf = cb_push(&cb, data_buf);
		assert(res_buf == data_buf);
	}

	data_buf = malloc(sizeof(int));
	*data_buf = BUF_CAPACITY;
	res_buf = cb_push(&cb, data_buf);
	assert(res_buf == NULL);
	free(data_buf);
	
	puts("\tok");

	printf("    cb_pop()");

	for (i = 0; i < BUF_CAPACITY; ++i) {
		data_buf = cb_pop(&cb);
		assert(*data_buf == i);
		free(data_buf);
	}
	assert(cb_pop(&cb) == NULL);
	assert(cb.size == 0);

	puts("\tok");
	
	cb_destroy(&cb);
	
	printf("    cb_destroy()");

	cb_init(&cb, BUF_CAPACITY, &free);
	for (i = 0; i < BUF_CAPACITY; ++i) {
		data_buf = malloc(sizeof(int));
		*data_buf = i;
		res_buf = cb_push(&cb, data_buf);
	}

	cb_destroy(&cb);
	assert(cb.size == 0);
	assert(cb.buffer == NULL);
	assert(cb.capacity == 0);

	puts("\tok");

	return 0;
}
