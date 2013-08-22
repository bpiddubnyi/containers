CFLAGS=-std=c99 -W -Wall -Werror -g
LIBCFLAGS=$(CFLAGS) -fPIC
LDFLAGS=-shared

default: all

%.o:%.c
	@echo "  CC $^"
	@$(CC) $(LIBCFLAGS) -o $@ -c $^
	@echo "  TEST $*"
	@$(CC) $(CFLAGS) -o $*_test $*_test.c $@
	@./$*_test;

libcontainers.so: list.o circular_buffer.o
	@echo "  LD $@"
	@$(CC) $(LDFLAGS) -o $@ $^

all: libcontainers.so

clean:
	@rm -rf *.o *.so *_test

.PHONY: clean default all
