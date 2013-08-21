#include <string.h>
#include <stdio.h>
#include <assert.h>

#include "list.h"

#define NODES_NUM 1024

int main() {
	node_t nodes[NODES_NUM];
	int data[NODES_NUM];
	list_t list;
	node_t *node_buf;
	int i;

	memset(&list, 0, sizeof(list_t));
	memset(nodes, 0, sizeof(node_t) * NODES_NUM);

	printf("    list_push_front()");
	for (i = 0; i < NODES_NUM; ++i) {
		data[i] = i;
		nodes[i].data = data + i;
		list_push_front(&list, nodes + i);
		assert((int)list.size == i + 1);
	}
	puts("\tok");
	
	printf("    list_pop_back()");
	for (i = 0; i < NODES_NUM; ++i) {
		node_buf = list_pop_back(&list);
		assert(*(int*)node_buf->data == i);
		assert((int)list.size == NODES_NUM - (i + 1));
	}
	assert(!list_pop_back(&list));
	assert(!list_pop_front(&list));
	puts("\tok");
	
	printf("    list_push_back)");
	for (i = 0; i < NODES_NUM; ++i) {
		data[i] = i;
		nodes[i].data = data + i;
		list_push_back(&list, nodes + i);
		assert((int)list.size == i + 1);
	}
	puts("\tok");
	
	printf("    list_pop_front()");
	for (i = 0; i < NODES_NUM; ++i) {
		node_buf = list_pop_front(&list);
		assert(*(int*)node_buf->data == i);
		assert((int)list.size == NODES_NUM - (i + 1));
	}
	assert(!list_pop_front(&list));
	assert(!list_pop_back(&list));
	puts("\tok");
}
