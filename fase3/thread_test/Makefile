CFLAGS ?=-Wall -Wextra -pthread -g
GCC ?=gcc $(CFLAGS)
BINARY_FILE ?= thread_test

.PHONY: all
all: build/all

.PHONY: build
build/all: main.c
	@echo "Starting to build the program"
	@$(GCC) -o $(BINARY_FILE) $^
	@echo "Finished program build"

.PHONY: clean
clean:
	@rm *.o

