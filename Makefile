CC = gcc
CFLAGS = -g -Wall -Wextra -Wlogical-op -Wjump-misses-init -Wdouble-promotion -Wshadow -Wformat=2 -Wmissing-prototypes -Wstrict-prototypes -pedantic -std=c99

all: spellcheck

spellcheck: spellcheck.c
	$(CC) $(CFLAGS) spellcheck.c llist_queue.c -o spellcheck

clean:
	rm -f spellcheck
	rm -f llist_queue
