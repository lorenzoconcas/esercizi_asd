#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define DIM_CODA 10
#define DIM_STACK 10
#define DIM 50

typedef struct {
    char articolo[DIM];
    double prezzo;
    char destinatario[DIM];
}Ordine;

typedef struct node {
    Ordine data;
    struct node* link;
}Node;

//rappresenta la nostra coda
typedef struct {
    Node* front;
    Node* back;
    int cont;
}Queue;

//Rappresenta lo stack
typedef struct {
    Node* top;
    int cont;
}Stack;

//prototipi funzioni per la gestione della Coda
_Bool isEmptyQueue(Queue*);
_Bool isFullQueue(Queue*);
void pushQueue(Queue*, Ordine);
Ordine popQueue(Queue*);
void printQueue(Queue*);
//...

//prototipi funzioni per la gestione dello Stack
_Bool isEmptyStack(Stack*);
_Bool isFullStack(Stack*);
void pushStack(Stack*, Ordine);
Ordine popStack(Stack*);
void printStack(Stack*);

//
void printStack(Stack* stack);
void printQueue(Queue* queue);

int main(void) {
    //dichiarazione e inizializzazione della Coda
    Queue queue;
    queue.front = NULL;
    queue.back = NULL;
    queue.cont = 0;

    //dichiarazione e inizializzazione dello Stack
    Stack stack;
    stack.top = NULL;
    stack.cont = 0;

    //variabili studente
    int choice = 0;
    _Bool cycle = true;
    Ordine ordine;
    ordine.prezzo = 0;

    while (cycle) {

#ifdef _WIN32
        system("cls");
#else 
        system("clear");
#endif
        printf("Liste");
        printf("\nChoose an option");
        printf("\n\t(1) Insert an order in queue \
                \n\t(2) Remove an order from queue \
                \n\t(3) Insert an order in stack for delivery \
                \n\t(4) Remove an order from stack \
                \n\t(5) Process first order in queue (Tail Pop) and prepare it for delivery (POP in stack) \
                \n\t(6) Print order queue status \
                \n\t(7) Print delivery stack status\
                \n\n\t(8) Exit");
        printf("\nChoice : ");

        do {
            scanf("%d", &choice);
            getchar();
            if (choice < 1 || choice > 8)
                printf("\nInvalid choice\nChoice : ");

        } while (choice < 1 || choice > 8);

        switch (choice)
        {
        case 1: {
            printf("\nInsert order name : ");
            scanf("%s", ordine.articolo);

            printf("\nInsert order price : ");
            scanf("%lf", &ordine.prezzo);

            printf("\nInsert order recipient : ");
            scanf("%s", ordine.destinatario);
            getchar();
            pushQueue(&queue, ordine);

            break;
        }
        case 2: {
            ordine = popQueue(&queue);
            printf("Order from queue : ");
            printf("\n\t\"%s\" Priced %lf for : %s", ordine.articolo, ordine.prezzo, ordine.destinatario);
            break;
        }
        case 3: {
            if (ordine.prezzo != 0)
                printf("\nPlease select an order before");
            else
                pushStack(&stack, ordine);
            break;
        }
        case 4:{
            ordine = popStack(&stack);
            printf("Order from queue : ");
            printf("\n\t\"%s\" Priced %lf for : %s", ordine.articolo, ordine.prezzo, ordine.destinatario);
            break;
        }
        case 5: {
            ordine = popQueue(&queue);
            printf("Order : ");
            printf("\n\t\"%s\" Priced %lf for : %s", ordine.articolo, ordine.prezzo, ordine.destinatario);
            printf("\t transferred to stack for delivery");
            pushStack(&stack, ordine);
            break;
        }
        case 6: {
            printQueue(&queue);
            break;
        }
        case 7: {
            printStack(&stack);
            break;
        }
        case 8: {
            cycle = false;
            printf("\nGoodbye");
            exit(0);
            break;
        }
        default:
            printf("To-DO");
            break;
        }
        printf("\nPress any key to continue");
        getchar();
    }

    return 0;
}

void printQueue(Queue* queue) {
    if (queue->cont == 0 || queue->front == NULL)
        printf("There's no element in queue");
    else {
        printf("There are %d (s) element(s) in queue\n", queue->cont);
        printf("Orders : ");
        Node* next = queue->front;
        while (next != NULL) {
            printf("\n\t\"%s\" Priced %lf for : %s", next->data.articolo, next->data.prezzo, next->data.destinatario);
            next = next->link;
        }
    }
}
void printStack(Stack* stack) {
    if (stack->cont == 0 || stack->top == NULL)
        printf("There's no element in stack");
    else {
        Node* next = stack->top;
        printf("There are %d (s) element(s) in stack", stack->cont);
        printf("Orders : ");
        while (next != NULL) {
            printf("\n\t\"%s\" Priced %lf for : %s", next->data.articolo, next->data.prezzo, next->data.destinatario);
            next = next->link;
        }
    }
}

_Bool isEmptyQueue(Queue* queue) {
    return (queue->cont == 0) ? true : false;
}
_Bool isFullQueue(Queue* queue) {
    return (queue->cont == DIM_CODA) ? true : false;
}
void pushQueue(Queue* queue, Ordine ordine) {
    if (isFullQueue(queue)) {
        printf("\nOverflow error");
        exit(-1);
    }

    Node* newNode = (Node*)malloc(sizeof(Node));

    newNode->data = ordine;
    newNode->link = NULL;

    if (isEmptyQueue(queue))
        queue->front = newNode;
    else
        queue->back->link = newNode;

    queue->back = newNode;
    queue->cont++;
}
Ordine popQueue(Queue* queue) {
    if (isEmptyQueue(queue)) {
        printf("\nUnderflow error");
        exit(-1);
    }
    else {

        Node* temp = queue->front;
        Ordine ordine = queue->front->data;

        if (queue->cont == 1) {
            queue->front = NULL;
            queue->back = NULL;
        }
        else
            queue->front = queue->front->link;

        queue->cont--;
        free(temp);
        return ordine;
    }
}
_Bool isEmptyStack(Stack* stack) {
    return (stack->cont == 0) ? true : false;
}
_Bool isFullStack(Stack* queue) {
    return (queue->cont == DIM_STACK) ? true : false;
}
void pushStack(Stack* stack, Ordine ordine) {
    if (isFullStack(stack)) {
        printf("Overflow error");
        exit(-1);
    }
    
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = ordine;
    newNode->link = NULL;
    stack->top = newNode;
    if (!isEmptyStack(stack))
        newNode->link = stack->top;

    stack->cont++;
}
Ordine popStack(Stack* stack) {
    if (isEmptyStack(stack)) {
        printf("Underflow error");
        exit(-1);
    }

    Node* temp = stack->top;
    Ordine ordine = stack->top->data;

    stack->top = stack->top->link;
    stack->cont--;
    free(temp);
    return ordine;
}