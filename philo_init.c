#include "philo.h"  

void  printf_mutix(int id, t_element *data, char *str)
{
    pthread_mutex_lock(data->print);
    printf("%lu %d %s", get_time() - data->start_time, id + 1, str);
    pthread_mutex_unlock(data->print);
}  

void *routine(void* arg)
{
    t_philo *philo = (t_philo *)arg;
    if (philo->id % 2 != 0)
        usleep(300);
    while(1)
    {
        pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
        printf_mutix(philo->id,  philo->data, "has taken a fork\n");
        pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
        printf_mutix(philo->id,  philo->data, "has taken a fork\n");
        pthread_mutex_lock(&philo->data->philo_data[philo->id]);
        philo->last_meal = get_time();
        philo->n_of_meals++;
        pthread_mutex_unlock(&philo->data->philo_data[philo->id]);
        printf_mutix(philo->id,  philo->data, "is eating\n");
        ft_usleep(philo->data->time_to_eat);
        pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
        pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
        printf_mutix(philo->id,  philo->data, "is sleeping\n");
        ft_usleep(philo->data->time_to_sleep);
        printf_mutix(philo->id,  philo->data, "is thinking\n");

    }
    return NULL;
}

void ft_kill_threads(t_element *data, int last_index)
{
    int i;

    i = 0;
    while (i < last_index)
    {
        pthread_join(data->philos[i].thread_id, NULL);
        i++;
    }
}

int thread_create(t_element *data)
{
    int i = 0;
    while (i < data->number_of_philosophers)
    {
        data->philos[i].last_meal = get_time();
        if (pthread_create(&data->philos[i].thread_id, NULL, routine, &data->philos[i])!= 0)
        {
            ft_kill_threads(data, i);
            return 1;
        }
        i++;
    }
    return 0;
}