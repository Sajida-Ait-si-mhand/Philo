#include "philo.h"

void *routine(void *arg)
{
    int *i = (int *) arg;
    while (*i < 10)
    {
    *i += 1;
    if (*i % 2 == 0)
        printf("I am thread number: %d\n", *i);
    }
}

int main(void)
{
    pthread_t philo1;
    pthread_t philo2;
    int *int_arra;
    int *arg;
    int_arra = malloc(sizeof(int) * 2); // 10

    arg = malloc(sizeof(int));
    *arg = 0;
    int i = 0;
    while (i < 2)
    {
        pthread_create(&philo1, NULL, routine, arg);
        i++;
    }
    sleep(2);
}