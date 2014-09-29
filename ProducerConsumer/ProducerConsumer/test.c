#include <stdlib.h>

int main()
{
    struct cs1550_sem *sem;

    sem = malloc(sizeof(sem));

    syscall(326, sem);
    return 0;
}