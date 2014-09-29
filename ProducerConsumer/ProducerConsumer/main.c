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
    Node *head;
    Node *tail;
    int value;
    //Some process queue of your devising
};


int enqueue(semaphore *, int);
int dequeue(semaphore *);


int main(int argc, char* argv[])
{
    semaphore semy;

    for(int i = 1; i < 10; i++)
    {
        enqueue(&semy, i);
    }

    for(int i = 1; i < 10; i++)
    {
        printf("%d\n", dequeue(&semy));
    }

    return 0;
}


int enqueue(semaphore *s, int task)
{ //and push on things that you put to sleep

    if(task == NULL) // If you're trying to add a blank node.
    {
        printf("Error adding node to queue");
        return -1;
    }

    Node *toAdd = malloc(sizeof(Node));


    toAdd->task = task;


    if(s->head == NULL) // If the head is null, add a new head.
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


int dequeue(semaphore *s)
{ // you pop off things you wake up

    if(s->head == NULL)
    {
        printf("Tried to dequeue from a empty list");
        return -1;
    }

    Node *retNode = s->head;
    int toReturn = (retNode->task);
    if(s->head->next == NULL)
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






















































/*

#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
struct cs1550_sem
{
    int value;
    //Some process queue of your devising
};

struct
{

    struct task_struct *task;
    struct Node *next;

} typedef Node;


int main(int argc, const char * argv[])
{
    //void *ptr = mmap(NULL, N, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);




    printf("Hello, World!\n");



    return 0;
}


Node *head;

Node *tail;
int enqueue(struct task_struct *task)
{
    if(task == NULL) // If you're trying to add a blank node.
    {
        //printk("Error adding node to queue");
        return -1;
    }

    Node *toAdd = malloc(sizeof(Node));
    toAdd->task = task;

    if(head == NULL) // If the head is null, add a new head.
    {
        head = toAdd;
        tail = toAdd;
    }
    else
    {
        tail->next = toAdd;
        tail = tail->next;
    }

    return 0;
}

struct task_struct dequeue()
{
    if(head == NULL)
    {
        //printk("Tried to dequeue from a empty list")
        return {-1};
    }

    Node *retNode = head;

    if(head->next == NULL)
    {
        head = NULL;
        free(head);
    }
    else
    {
        Node *prevHead = head;
        head = head->next;
        free(prevHead);
    }

    */
/*
     * This doesn't feel like it should work........
     *//*

    return *retNode->task;
}



*/
