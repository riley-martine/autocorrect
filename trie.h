typedef struct trie_node {
    struct trie_node* next;
    struct trie_node* child;
    char symbol;
    bool is_word;
} TrieNode;

TrieNode* init_trie(void);
void free_trie(TrieNode* tn);
void insert_trie(TrieNode* tn, char* s);
void print_trie(TrieNode* tn);
bool trie_contains(TrieNode* tn, char* s);
int test_trie(void);
