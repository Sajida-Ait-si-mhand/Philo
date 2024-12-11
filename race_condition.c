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
    pthread_t p1, p2;
    pthread_mutex_init(&mutix, NULL);
    int i = 0;
    while(i < 200)
    {
        if (pthread_create(&p1, NULL, routine, NULL))
        return 1;
        // if (pthread_create(&p2, NULL, routine, NULL))
        //     return 1;
        i++;
    }
      for (int i = 0; i < 200; i++)
    {
        pthread_join(p1, NULL);
    }
    pthread_mutex_destroy(&mutix);
    printf("number_of_meals: [%d]\n", mails);
    // usleep(1);//
    return 0;
}