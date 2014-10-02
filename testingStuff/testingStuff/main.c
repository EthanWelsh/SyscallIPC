#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
struct Node
{
    int *task;
    Node *next;
};

typedef struct cs1550_sem semaphore;
struct cs1550_sem
{
    Node *head;
    Node *tail;
};


void printList(semaphore *s);
int *dequeue(semaphore *s);

int main(int argc, const char * argv[])
{

    semaphore *s = malloc(sizeof(semaphore));

    s->head = NULL;
    s->tail = NULL;

    return 0;
}


int enqueue(semaphore *s, int *task)
{ //and push on things that you put to sleep
    Node *toAdd = malloc(sizeof(Node));

    if ((s->head == NULL) || (s-> tail == NULL)) // If the head is null, add a new head.
    {
        s->head = toAdd;
        s->tail = toAdd;
        s->tail->next = NULL;
    }
    else
    {
        s->tail->next = toAdd;
        s->tail = s->tail->next;
        s->tail->next = NULL;
    }

    toAdd->task = task;

    return 0;
}


void printList(semaphore *s)
{
    Node *curr = s->head;

    while(curr != NULL)
    {
        printf("%d\n", *(curr->task));
        curr = curr->next;
    }

    return;

}



int *dequeue(semaphore *s)
{ // you pop off things you wake up

    if((s->head == NULL) || (s->tail == NULL))
    {
        printf("ERORROROROROR!\n");
        while(1);
        return -1;
    }
    else
    {
        struct task_struct *tsk = s->head->task;
        if(s->head->next == NULL)
        {
            free(s->head);
            s->head = NULL;
            s->tail = NULL;
            return tsk;
        }
        else
        {
            Node *oldhead = s->head;
            s->head = s->head->next;
            free(oldhead);
            return tsk;
        }
    }
}