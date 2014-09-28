#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;

struct Node
{
    int *task;
    Node *next;

};


int enqueue(int);
int dequeue();

Node *head;
Node *tail;





int main(int argc, const char * argv[])
{
    //void *ptr = mmap(NULL, N, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);

    for(int i = 1; i < 10; i++)
    {
        enqueue(i);
    }


    dequeue();


    printf("DONE");

    return 0;
}


int enqueue(int task)
{
    printf("\n\n");

    if(!head == NULL) printf("~~1~~HEAD:%d\n",*head->task);

    if(task == NULL) // If you're trying to add a blank node.
    {
        printf("Error adding node to queue");
        return -1;
    }

    if(!head == NULL) printf("~~2~~HEAD:%d\n",*head->task);
    Node *toAdd = malloc(sizeof(Node));

    if(!head == NULL) printf("~~3~~HEAD:%d\n",*head->task);
    toAdd->task = &task;
    if(!head == NULL) printf("~~4~~HEAD:%d\n",*head->task);


    if(head == NULL) // If the head is null, add a new head.
    {
        head = toAdd;

        printf("~~5~~HEAD:%d\n",*head->task);

        tail = toAdd;
        printf("~~6~~HEAD:%d\n",*head->task);
    }
    else
    {
        printf("~~7~~HEAD:%d\n",*head->task);
        tail->next = toAdd;


        printf("~~8~~HEAD:%d\n",*head->task);
        tail = tail->next;

        printf("~~9~~HEAD:%d\n",*head->task);
    }

        printf("~~10~~HEAD:%d\n",*head->task);
    return 0;
}


int dequeue()
{
    if(head == NULL)
    {
        printf("Tried to dequeue from a empty list");
        return -1;
    }

    //printf("~~1~~HEAD:%d\n",*head->task);

    Node *retNode = head;

    //printf("~~2~~HEAD:%d\n",*head->task);

    int toReturn = *(retNode->task);

    //printf("~~3~~HEAD:%d\n",*head->task);

    if(head->next == NULL)
    {
       // printf("~~4~~HEAD:%d\n",*head->task);
        free(head);
       // printf("~~5~~HEAD:%d\n",*head->task);
        head = NULL;
        //printf("~~6~~HEAD:%d\n",*head->task);
    }
    else
    {
        //printf("~~7~~HEAD:%d\n",*head->task);
        Node *prevHead = head;
        //printf("~~8~~HEAD:%d\n",*head->task);
        head = head->next;
        //printf("~~9~~HEAD:%d\n",*head->task);
        free(prevHead);
        //printf("~~10~~HEAD:%d\n",*head->task);
    }

    //printf("~~11~~HEAD:%d\n",*head->task);
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
