#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "llist_queue.h"

// Queues are FIFO data structures
// I will implement init, push, pop, peek, clear, and isEmpty methods.
// I will use a doubly-linked list, and keep track of both ends.

int test(void){
  
	Queue* queue = initQueue();

    if(isEmpty(queue) == 1) {
        puts("WIN: isEmpty can detect empty before adding");
    } else {
        puts("ERROR: isEmpty fails before adding");
    }

    push(queue, "dd");
    push(queue, "aa");
    push(queue, "bb");
    printQueue(queue);
 
    if(isEmpty(queue) == 0) {
        puts("WIN: isEmpty can detect empty after adding");
    } else {
        puts("ERROR: isEmpty fails after adding");
    }


    if( strcmp(peek(queue), "dd") == 0) { 
        puts("WIN: Peek views first inserted element");
    } else {
        puts("ERROR: Peek does not view first inserted element.");
        printf("       expected: {dd} got: {%s}\n", peek(queue));
    }

    if( strcmp(peek(queue), "dd") == 0 ) {
        puts("WIN: Peek does not pop.");
    } else {
        puts("ERROR: Peek may change stack");
    }

    if( strcmp(pop(queue), "dd") == 0 ) {
        puts("WIN: Pop returns last inserted element");
    } else {
        puts("ERROR: Pop does not return last inserted element.");
    }

    if( strcmp(pop(queue), "aa") == 0) {
        puts("WIN: Pop removes element");
    } else {
        puts("ERROR: Pop may not remove from stack");
    }

    if( strcmp(pop(queue), "bb") == 0) {
        puts("WIN: Pop removes last element");
    } else {
        puts("ERROR: Pop does not remove last element.");
    }

    if(! pop(queue)) {
        puts("WIN: Pop does not bail on an empty stack");
    } else {
        puts("ERROR: Pop bails on an empty stack.");
    }
    
    if(! peek(queue)) { 
        puts("WIN: Peek does not bail on an empty stack");
    } else {
        puts("ERROR: Peek bails on an empty stack");
    }

    if(isEmpty(queue) == 1) {
        puts("WIN: isEmpty can detect empty before re-init");
    } else {
        puts("ERROR: isEmpty fails before re-init");
    }

    push(queue, "yes");

    if( strcmp(peek(queue), "yes") == 0){
        puts("WIN: We can read from the stack after re-init");
    } else {
        puts("ERROR: Does not read correctly from re-init");
    }

    clear(queue);

    if( isEmpty(queue) == 1 ) {
        puts("WIN: Clear clears stack");
    } else {
        puts("ERROR: Clear does not clear stack.");
    }

    return 0;
}


Queue *initQueue(void){
    Queue *queue = malloc(sizeof(Queue));
    queue->first = NULL;
    queue->last  = NULL;
    return queue;
}


void push(Queue* queue, char* datum){
    char* copy = malloc(strlen(datum) + 1); 
    strcpy(copy, datum);
    if(!(queue)->first) {
	    ListNode *newNode = malloc(sizeof(ListNode));
	    newNode->datum  = copy;
	    newNode->next   = NULL;
        newNode->prev   = NULL;
        queue->first    = newNode;
        queue->last     = newNode;
        return;
    }
    // If there is more than 1 node
    
	ListNode *newNode = malloc(sizeof(ListNode));
	newNode->datum = copy;
	newNode->next  = (queue)->first;
    newNode->prev  = NULL;
    newNode->next->prev = newNode;
    (queue)->first = newNode;
    return;
}

char* pop(Queue *queue) {
    if(!queue->last) {
        return '\0'; //uhhh
    }
    ListNode *toPop   = (queue)->last;
    ListNode *newTail = (queue)->last->prev;
    if(queue->first == queue->last) {
        queue->first = NULL;
    }
    queue->last = newTail;
    char* ret = toPop->datum;
    free(toPop);
    return ret;
}

char* peek(Queue* queue) {
    if(!(queue->last)) {
        return '\0'; //uhhh
    }
    return (queue->last)->datum;
}

void clear(Queue* queue) {
    while(!isEmpty(queue))
        pop(queue);
    return;
}

int isEmpty(Queue* queue) {
    if(!(queue->first))
        return 1;
    return 0;

}

void printQueue(Queue* queue) {
    ListNode *cur = queue->last;
    while(cur){
        printf("%s|", cur->datum);
        cur = cur->prev;
    }
    puts("");
}
