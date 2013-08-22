#include <string.h>

#include "unit_test.h"
#include "list.h"

#define NODES_NUM 1024

UNIT_START
	node_t nodes[NODES_NUM];
	int data[NODES_NUM];
	list_t list;
	node_t *node_buf;
	int i;

	memset(&list, 0, sizeof(list_t));
	memset(nodes, 0, sizeof(node_t) * NODES_NUM);

	TEST_START("list_push_front()");
	for (i = 0; i < NODES_NUM; ++i) {
		data[i] = i;
		nodes[i].data = data + i;
		list_push_front(&list, nodes + i);
		CHECK_EQUAL((int)list.size, i + 1);
	}
	TEST_END;
	
	TEST_START("list_pop_back()");
	for (i = 0; i < NODES_NUM; ++i) {
		node_buf = list_pop_back(&list);
		CHECK_EQUAL(*(int*)node_buf->data,  i);
		CHECK_EQUAL((int)list.size, NODES_NUM - (i + 1));
	}
	CHECK_IF(!list_pop_back(&list));
	CHECK_IF(!list_pop_front(&list));
	TEST_END;
	
	TEST_START("list_push_back)");
	for (i = 0; i < NODES_NUM; ++i) {
		data[i] = i;
		nodes[i].data = data + i;
		list_push_back(&list, nodes + i);
		CHECK_EQUAL((int)list.size, i + 1);
	}
	TEST_END;
	
	TEST_START("list_pop_front()");
	for (i = 0; i < NODES_NUM; ++i) {
		node_buf = list_pop_front(&list);
		CHECK_EQUAL(*(int*)node_buf->data,  i);
		CHECK_EQUAL((int)list.size, NODES_NUM - (i + 1));
	}
	CHECK_IF(!list_pop_front(&list));
	CHECK_IF(!list_pop_back(&list));
	TEST_END;
UNIT_END
