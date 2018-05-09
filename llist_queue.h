typedef struct listNode {
    char* datum;
    struct listNode* next;
    struct listNode* prev;
} ListNode;

typedef struct queue {
    ListNode* first;
    ListNode* last;
} Queue;

Queue *initQueue(void);
void push(Queue* head, char* datum);
char* pop(Queue* head);
char* peek(Queue* head);
void clear(Queue* head);
int isEmpty(Queue* head);
void printQueue(Queue* head);
int test(void);
