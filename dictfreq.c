#define _SVID_SOURCE

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "dictfreq.h"


// We should store the dictionary in a STATIC SET.
// It will be unindexed, packaged, and unchanging. 
// The set implementation should be optimized for
//     the function is_element_of(x,S).
// Lists have membership checking of O(n). This isn't
//     very good.
// I will use a prefix tree/radix tree/trie, because
//     it is simpler than hash maps and thus easier
//     to reason about and harder to mess up.
char* dict_file_contents(void) {
    static char* contents = NULL;

    if (contents == NULL) {
        FILE* fp = fopen("words.txt", "r");
        
        fseek(fp, 0L, SEEK_END);
        int sz = ftell(fp);
        rewind(fp);

        contents = malloc(sz);

        fread(contents, sizeof(char), sz, fp);

        fclose(fp);
    }

    return contents;
}

bool is_dictionary_word(char* s) {
    char* dict = dict_file_contents();
    int i;
    char* p = malloc(sizeof(char) * (strlen(s) + 2));
    p[0] = '\n';
    for(i = 1; s[i-1]; i++){
        p[i] = s[i-1];
    }
    p[i] = '\n';
    p[i+1] = '\0';
    //printf("\nBB\n%s\n$$%sEE\n", s, p);
    if (strstr(dict, p) != NULL) {
        return true;
    }

    return false;
}

void free_dict(void) {
    free(dict_file_contents());
}
