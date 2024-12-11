#include "philo.h"

int mails = 0;
int lock = 0;
pthread_mutex_t mutix; 

void *routine(void* arg)
{
    pthread_mutex_lock(&mutix);
    while (mails < 1500000)
    {
        mails++;
    }
    pthread_mutex_unlock(&mutix);
    
}
int main(void)
{
    pthread_t th[200];
    pthread_mutex_init(&mutix, NULL);
    int i = 0;
    while(i < 200)
    {
        if (pthread_create(&th[i], NULL, routine, NULL))
            return 1;
        printf(" \033[34mthread has started:%d \033[0m", i);
        
        i++;
    }
    i = 0;
    while (i < 200)
    {
        if (pthread_join(th[i], NULL))
            return 1;
        i++;
    }
    printf(" \033[37m Finish the execution: \033[0m\n");
    pthread_mutex_destroy(&mutix);
    printf("number_of_meals: [%d]\n", mails);
    return 0;
}