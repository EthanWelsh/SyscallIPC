#define N 500

#include <stdlib.h>
#include <stdio.h>

int main()
{
    struct cs1550_sem *sem;


    void *ptr = mmap(NULL, N, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, 0, 0);

    int *arr = ptr;

    for(int i = 0; i < 100; i++) arr[i] = 20;
    for(int i = 0; i < 100; i++) printf("%d\n", arr[i]);


    sem = malloc(sizeof(sem));

    syscall(326, sem);
    return 0;
}