#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include "trie.h"

//#define DEBUG

#ifdef DEBUG
    #define d_puts(...) puts(__VA_ARGS__);
    #define d_printf(...) printf(__VA_ARGS__);
#endif

#ifndef DEBUG
    #define d_puts(...) ;
    #define d_printf(...) ;
#endif


int main(void) {

    TrieNode* tn = init_trie();

    insert_trie(tn, "she");
    insert_trie(tn, "sells");
    insert_trie(tn, "sea");
    insert_trie(tn, "shells");
    insert_trie(tn, "by");
    insert_trie(tn, "the");
    insert_trie(tn, "seashore");

    TrieNode* cur = tn;
    while(cur) {
        printf("%c|%d|", cur->symbol, cur->is_word);
        cur = cur->child;
    }
    printf("\n");

    print_trie(tn);
    printf("\n");

    printf("She: %d\n", trie_contains(tn, "she"));
    printf("Sells: %d\n", trie_contains(tn, "sells"));
    printf("Sea: %d\n", trie_contains(tn, "sea"));
    printf("Shells: %d\n", trie_contains(tn, "shells"));
    printf("By: %d\n", trie_contains(tn, "by"));
    printf("The: %d\n", trie_contains(tn, "the"));
    printf("Seashore: %d\n", trie_contains(tn, "seashore"));

    printf("He: %d\n", trie_contains(tn, "he"));
    printf("Smells: %d\n", trie_contains(tn, "smells"));
    printf("Seashor: %d\n", trie_contains(tn, "seashor"));
    printf("Seashoreees: %d\n", trie_contains(tn, "seashor"));
    printf("Seash: %d\n", trie_contains(tn, "seash"));
    printf("Seas: %d\n", trie_contains(tn, "seas"));
    printf("Shell: %d\n", trie_contains(tn, "shell"));
    printf("Shel: %d\n", trie_contains(tn, "shel"));

    return 0;
}

TrieNode* init_trie(void) {
    TrieNode* tn = malloc(sizeof(TrieNode));
    tn->next = NULL;
    tn->child = NULL;
    tn->symbol = '\0';
    tn->is_word = false;
    return tn;
}


bool trie_contains(TrieNode* tn, char* s) {
    TrieNode* cur = tn;

    while (cur != NULL) {
        if (cur->symbol == s[0]) {
            char* ss = ++s;

            if (strlen(ss) == 0) {
                return cur->is_word;
            }

            return trie_contains(cur->child, ss);
        }
        cur = cur->next;
    }
    return false;
}

void print_trie(TrieNode* tn) {
    TrieNode* cur_base = tn;
    TrieNode* prev;
    while (cur_base != NULL) {
        d_puts("Not null");
        printf("%c", cur_base->symbol);
        
        if (cur_base->is_word) {
            printf("|");
        }
        print_trie(cur_base->child);
        prev = cur_base;
        cur_base = cur_base->next;
    }
    return;
}

void insert_trie(TrieNode* tn, char* s) {
    TrieNode* cur = tn;
    TrieNode* prev = NULL;
    
    d_puts("Entered Function");
    d_printf("%c\n", s[0]);

    if (strlen(s) == 0) {
        d_puts("Insert done");
        tn->is_word = true;
        return;
    }

    while(cur != NULL) {
        if(cur->symbol == s[0]){
            d_puts("Found first char");
            goto found;
        }
        prev = cur;
        cur = cur->next;
    }

    if(prev->next == NULL) { // Did not find first character
        d_puts("Did not find first char");
        if(prev->symbol == '\0') {
            d_puts("Is first node of trie");
            prev->symbol = s[0];
            d_puts("Assigned symbol");
            
            char* ss = ++s;
            if (strlen(ss) == 0) {
                prev->is_word = true;
                return;
            }
            prev->child = init_trie();
            insert_trie(prev->child, ss);
            return;

        } else {
            prev->next = init_trie();
            d_puts("Initialized tree");
            prev->next->symbol = s[0];
            d_puts("Assigned symbol");
            d_printf("%c\n", prev->next->symbol);
        }
    }
    
    found: {
        char* ss = ++s;
        

        if (prev == NULL) { // we are on first character
            d_puts("Prev is null");
            if (strlen(ss) == 0) {
                prev->is_word = true;
                return;
            }
            if (cur->child == NULL) {
                cur->child = init_trie();
            }
            insert_trie(cur->child, ss);
            return;
        } else if (prev->next->child == NULL && strlen(ss) != 0) {
            prev->next->child = init_trie();
        }
        if (strlen(ss) == 0) {
            prev->next->is_word = true;
            return;
        }
        insert_trie(prev->next->child, ss);
        return;
    }
}
