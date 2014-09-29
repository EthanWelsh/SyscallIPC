#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node
{
    int task;
    Node *next;
};

typedef struct cs1550_sem semaphore;
struct cs1550_sem
{
    int value;
    Node *head;
    Node *tail;
};

int enqueue(semaphore *, struct task_struct);

struct task_struct dequeue(semaphore *);

int enqueue(semaphore *s, struct task_struct task)
{ //and push on things that you put to sleep

    if (task == NULL) // If you're trying to add a blank node.
    {
        printf("Error adding node to queue");
        return -1;
    }

    Node *toAdd = malloc(sizeof(Node));


    toAdd->task = task;


    if (s->head == NULL) // If the head is null, add a new head.
    {
        s->head = toAdd;
        s->tail = toAdd;
    }
    else
    {
        s->tail->next = toAdd;
        s->tail = s->tail->next;
    }
    return 0;
}


struct task_struct dequeue(semaphore *s)
{ // you pop off things you wake up

    if (s->head == NULL)
    {
        return NULL;
    }

    Node *retNode = s->head;
    struct task_struct toReturn = (retNode->task);
    if (s->head->next == NULL)
    {
        free(s->head);
        s->head = NULL;
    }
    else
    {
        Node *prevHead = s->head;
        s->head = s->head->next;
        free(prevHead);
    }

    return toReturn;
}