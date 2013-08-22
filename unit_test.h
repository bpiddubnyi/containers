#ifndef __UNIT_TEST_H__
#define __UNIT_TEST_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ERR_BUF_SIZE 1024

#define UNIT_START \
int main() { \
	unsigned int tests_passed; \
	unsigned int tests_total; \
	unsigned int fail = 0; \
	char err_buf[ERR_BUF_SIZE];

#define UNIT_END \
end: \
	tests_total = __COUNTER__; \
	if (fail) { \
		printf("\tfail\n%s\n", err_buf); \
		fsync(STDOUT_FILENO); \
	} \
	printf("\nPassed %u tests from %u\n", tests_passed, tests_total); \
	if (fail) { \
		abort(); \
	} else { \
		return 0;\
	} \
}

#define TEST_START(test_name) \
do { \
	printf("%d %s",__COUNTER__ + 1, test_name); \
	fsync(STDOUT_FILENO); \
} while(0)

#define TEST_END \
do { \
	++tests_passed; \
	puts("\tok"); \
	fsync(STDOUT_FILENO); \
} while(0)

#define _STR(x) #x
#define STR(x) _STR(x)
#define LINE_STR STR(__LINE__)

#define UNIT_TEST_ERR(fmt, ...) \
do { \
	snprintf(err_buf, ERR_BUF_SIZE, "Error: " fmt " on " \
		 __FILE__ ":" LINE_STR, ##__VA_ARGS__); \
	fsync(STDOUT_FILENO); \
	fail = 1; \
	goto end; \
} while(0)

#define CHECK_IF(exp) \
do { \
	if (!(exp)) { \
		UNIT_TEST_ERR(#exp); \
	}\
} while(0)

#define CHECK_EQUAL(a, b) \
do { \
	if ((a) != (b)) { \
		UNIT_TEST_ERR(#a " != " #b); \
	} \
} while(0)

#endif /* __UNIT_TEST_H__ */
