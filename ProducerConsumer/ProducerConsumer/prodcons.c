#include <stdio.h>
#include <stdlib.h>

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
        printk("PRODUCING %d at position %d\n", pitem, in);
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
        printk("CONSUMING %d at position %d\n", citem, out);
        up(mutex);
        up(&empty);


    }
    return 0;
}

void down(struct cs1550_sem *sem)
{
    syscall(__NR_cs1550_down, sem);
}

int up(struct cs1550_sem *sem)
{
    syscall(__NR_cs1550_up, sem);
}