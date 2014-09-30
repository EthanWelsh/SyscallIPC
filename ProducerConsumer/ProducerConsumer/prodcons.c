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


// PROTOTYPES
void down(struct cs1550_sem *);
void up(struct cs1550_sem *);


//globals
struct cs1550_sem *empty;
struct cs1550_sem *full;
struct cs1550_sem *mutex;
 //-----------------------//
int *buffer;
int num_of_elements;


int main (int argc, char *argv[])
{
    if(argc != 4)
    { // Check for correct format.
        printf("Valid format is: prodcons 2 2 1000\n");
        return -1;
    }

    // Get command line arguments
    int num_of_prod = atoi(argv[1]);
    int num_of_cons = atoi(argv[2]);
    num_of_elements = atoi(argv[3]);

    // Set up shared memory for the following...
    mutex = mmap(NULL, sizeof(struct cs1550_sem), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0); // mutex semaphore
    full = mmap(NULL, sizeof(struct cs1550_sem), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);  // full semaphore
    empty = mmap(NULL, sizeof(struct cs1550_sem), PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0); // empty semaphore
    buffer = mmap(NULL, num_of_elements, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0); // shared array to be subject to race condition

    empty->value = num_of_elements; // Start with N number of empty cells in the array
    mutex->value = 1; // Set the mutex at one in order to establish atomicity of instructions
    full->value = 0; // Start with 0 full cells in the array

    int i = 0;
    int f = 0;

    // Loop around N number of times, where N is the number of producers you want to create plus the number of consumers.
    for(i = 0; i < (num_of_prod + num_of_cons); i++)
    {
        f = fork();
        if(f == -1)
        {
            printf("Something went very, very, very badly.\n");
            return -1;
        }
        else if (f == 0) continue; // if we're the parent, continue creating more producers and consumers.
        else break; // otherwise, we're a child so let's become a producer or consumer...
    }

    if(f == 0) return 0; // stop execution of the parent because it has already created all producers and consumers.
    if(i < num_of_prod) produce(); // create producers
    else consume(); // create consumers
    return 0;
}


int produce()
{
    int in = 0;
    int pitem = 2;

    while (1)
    {
        down(empty); // check if there are empty cells in our array to put things in
        down(mutex); // enter critical region

        buffer[in] = pitem;

        in = (in + 1) % num_of_elements; // circular increment

        printf("PRODUCING %d at position %d\n", pitem, in);

        up(mutex); // leave critical region
        up(full);  // we've not got one more full cell in our array now that we've produced one.
    }
    return 0;
}


int consume()
{
    int out = 0;
    int citem = 0;

    while (1)
    {
        down(full); // check if there are full cells in the array to take things from
        down(mutex); // enter critical region

        citem = buffer[out];

        out = (out+1) % num_of_elements; // circular increment

        printf("CONSUMING %d at position %d\n", citem, out);

        up(mutex); // leave critical region
        up(empty); // we've got one more empty cell in our array now that we've consumer one.
    }
    return 0;
}

// helper functions to make syscalls
void down(struct cs1550_sem *sem)
{
    syscall(326, sem);
    return;
}

void up(struct cs1550_sem *sem)
{
    syscall(327, sem);
    return;
}