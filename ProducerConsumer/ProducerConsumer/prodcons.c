#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>


typedef struct cs1550_sem semaphore;

struct cs1550_sem
{
    int value;
    void *head;
    void *tail;
};



struct cs1550_sem *empty;
struct cs1550_sem *full;
struct cs1550_sem *mutex;


int *buffer;
int num_of_elements;




int main (int argc, char *argv[])
{
    if(argc != 4)
    { // Check for correct format.
        printf("Valid format is: prodcons 2 2 1000\n");
        return -1;
    }

    int num_of_prod = argv[1];
    int num_of_cons = argv[2];
    int num_of_elements = argv[3];

    mutex = mmap(NULL, sizeof(struct cs1550_sem), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);
    full = mmap(NULL, sizeof(struct cs1550_sem), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);
    empty = mmap(NULL, sizeof(struct cs1550_sem), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);
    buffer = mmap(NULL, num_of_elements, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);

    int tid = 0;

    for(tid = 0; tid < num_of_prod + num_of_cons; tid++)
    {
        int f = fork();
        if(f == -1)
        {
            printf("Something went very, very, very badly.\n");
            return -1;
        }
        else if (f == 0) continue;
        else break;
    }

    if(tid < num_of_cons) consume();
    else produce();
}


int produce()
{
    int in = 0;
    int pitem = 2;

    while (1)
    {
        down(empty);
        down(mutex);
        buffer[in] = pitem;
        in = (in+1) % num_of_elements;
        printf("PRODUCING %d at position %d\n", pitem, in);
        up(mutex);
        up(full);
    }
    return 0;
}


int consume()
{
    int out = 0;
    int citem = 0;

    while (1)
    {
        down(&full);
        down(mutex);
        citem = buffer[out];
        out = (out+1) % num_of_elements;
        printf("CONSUMING %d at position %d\n", citem, out);
        up(mutex);
        up(&empty);
    }
    return 0;
}

void down(struct cs1550_sem *sem)
{
    syscall(326, sem);
}

int up(struct cs1550_sem *sem)
{
    syscall(327, sem);
}