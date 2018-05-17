CC = gcc
CFLAGS = -g -Wall -Wextra -Wlogical-op -Wjump-misses-init -Wdouble-promotion -Wshadow -Wformat=2 -Wmissing-prototypes -Wstrict-prototypes -pedantic -std=c99

all: spellcheck

spellcheck: spellcheck.c
	$(CC) $(CFLAGS) spellcheck.c llist_queue.c dictfreq.c -o spellcheck

dictfreq: dictfreq.c
	$(CC) $(CFLAGS) dictfreq.c -o dictfreq

trie: trie.c
	$(CC) $(CFLAGS) trie.c -o trie

clean:
	rm -f spellcheck
	rm -f llist_queue
	rm -f dictfreq
	rm -rf trie
