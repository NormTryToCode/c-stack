#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int info;
    struct Node* next;
} NodeObject;


void push(NodeObject** top_of_stack, int e){
    NodeObject* newNode = (NodeObject*)malloc(sizeof(NodeObject));
    newNode->info = e;
    newNode->next = NULL;
    newNode->next = *top_of_stack;
    *top_of_stack = newNode;

}

int countStackElements(NodeObject* top_of_stack){
    NodeObject* currentNode = top_of_stack;
    int result = 0;
    if (currentNode == NULL){
        return result;
    }
    else {
        while (currentNode != NULL){
            currentNode = currentNode->next;
            result += 1;
        }
    }
    return result;
}

NodeObject* pop(NodeObject** top_of_stack, NodeObject** back_of_stack){
    NodeObject* placeholder = *top_of_stack;
    *top_of_stack = (*top_of_stack)->next;
    *back_of_stack = *top_of_stack;
    return placeholder;

}

void printStack(NodeObject* top_of_stack){
    NodeObject* currentNode = top_of_stack;
    int elementCount = countStackElements(top_of_stack);

    if (currentNode == NULL){
        printf("[]\n");
        return;
    }
    printf("[");
    while (currentNode != NULL){
        if (currentNode->next != NULL){
            printf("%d, ", currentNode->info);
        }
        else {
            printf("%d]\n", currentNode->info);
        }
        currentNode = currentNode->next;
    }
}


int main(){
    NodeObject* top_of_stack = NULL;
    NodeObject* bottom_of_stack = NULL;
    printStack(top_of_stack);
    push(&top_of_stack, 1);
    push(&top_of_stack, 2);
    push(&top_of_stack, 3);

    printStack(top_of_stack);

    NodeObject* PoppedNode = pop(&top_of_stack, &bottom_of_stack);
    printStack(top_of_stack);
    pop(&top_of_stack, &bottom_of_stack);
    printStack(top_of_stack);
}