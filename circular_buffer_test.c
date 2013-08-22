#include "unit_test.h"
#include "circular_buffer.h"

#define BUF_CAPACITY 1024 

UNIT_START
	cb_t cb;
	int i;
	int *data_buf, *res_buf;

	TEST_START("cb_init()");
	
	cb_init(&cb, BUF_CAPACITY, NULL);
	CHECK_IF(cb.buffer);
	
	TEST_END;

	TEST_START("cb_push()");
	
	for (i = 0; i < BUF_CAPACITY; ++i) {
		data_buf = malloc(sizeof(int));
		*data_buf = i;
		res_buf = cb_push(&cb, data_buf);
		CHECK_EQUAL(res_buf, data_buf);
	}

	data_buf = malloc(sizeof(int));
	*data_buf = BUF_CAPACITY;
	res_buf = cb_push(&cb, data_buf);
	CHECK_EQUAL(res_buf, NULL);
	free(data_buf);
	
	TEST_END;

	TEST_START("cb_pop()");

	for (i = 0; i < BUF_CAPACITY; ++i) {
		data_buf = cb_pop(&cb);
		CHECK_EQUAL(*data_buf, i);
		free(data_buf);
	}
	CHECK_EQUAL(cb_pop(&cb), NULL);
	CHECK_EQUAL(cb.size, 0);

	TEST_END;
	
	cb_destroy(&cb);
	
	TEST_START("cb_destroy()");

	cb_init(&cb, BUF_CAPACITY, &free);
	for (i = 0; i < BUF_CAPACITY; ++i) {
		data_buf = malloc(sizeof(int));
		*data_buf = i;
		res_buf = cb_push(&cb, data_buf);
	}

	cb_destroy(&cb);
	CHECK_EQUAL(cb.size, 0);
	CHECK_EQUAL(cb.buffer, NULL);
	CHECK_EQUAL(cb.capacity, 0);

	TEST_END;
UNIT_END
