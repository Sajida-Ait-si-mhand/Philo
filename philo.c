#include "philo.h"


void ft_mutix_destory(pthread_mutex_t *mutix_array, int last_index)
{
    int i;

    i = 0;
    while (i < last_index)
    {
        pthread_mutex_destroy(&mutix_array[i]);
        i++;
    }
    free(mutix_array);
}

t_philo *philos_init(t_element *data)
{
    int i;
    t_philo *philo;

    i = 0;
    philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
    if (!philo)
        return NULL;
    memset(philo, 0, sizeof(t_philo) * data->number_of_philosophers);
    while (i < data->number_of_philosophers)
    {
        philo[i].id = i;
        if (i % 2 == 0)
        {
        philo[i].left_fork = i;
        philo[i].right_fork = (i + 1) % data->number_of_philosophers;
        }
        else
        {   
        philo[i].right_fork = i;
        philo[i].left_fork = (i + 1) % data->number_of_philosophers;
        }
        philo[i].n_of_meals = 0;
        philo[i].data = data;
        i++;
    }
    return philo;
}

pthread_mutex_t  *philo_data_init(t_element *data)
{
    pthread_mutex_t *philo_data;
    int i;

    i = 0;
    philo_data = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    if (!philo_data)
        return NULL;
    memset(philo_data, 0, sizeof(pthread_mutex_t) * data->number_of_philosophers);
    while (i < data->number_of_philosophers)
    {
        if (pthread_mutex_init(&philo_data[i], NULL) != 0)
            return(ft_mutix_destory(philo_data, i), NULL);
        i++;
    }
    return philo_data;
}
pthread_mutex_t *forks_init(t_element *data)
{
    pthread_mutex_t *forks;
    int i;

    i = 0;
    forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
    if (!forks)
        return NULL;
    memset(forks, 0, sizeof(pthread_mutex_t) * data->number_of_philosophers);
    while (i < data->number_of_philosophers)
    {
        if (pthread_mutex_init(&forks[i], NULL) != 0)
            return(ft_mutix_destory(forks, i), NULL);
        i++;
    }
    return forks;
}

pthread_mutex_t *print_init()
{
    pthread_mutex_t *print;

    print = malloc(sizeof(pthread_mutex_t));
    if (!print)
        return NULL;
    if (pthread_mutex_init(print, NULL) != 0)
        return(ft_mutix_destory(print, 1), NULL);
    return print;
}

pthread_mutex_t *alive_mutex_init()
{
    pthread_mutex_t *alive_mutex;

    alive_mutex = malloc(sizeof(pthread_mutex_t));
    if (!alive_mutex)
        return NULL;
    if (pthread_mutex_init(alive_mutex, NULL) != 0)
        return(ft_mutix_destory(alive_mutex, 1), NULL);
    return alive_mutex;
}   

int data_init(t_element *data)
{
    data->alive = true;
    data->philos = philos_init(data);
    data->philo_data = philo_data_init(data);
    data->forks = forks_init(data);
    data->print = print_init();
    data->alive_mutex = alive_mutex_init();
    if (!data->philos || !data->philo_data || !data->forks || !data->print || !data->alive_mutex)
        return 1;
    return 0;
}

int main(int ac, char *av[])
{
    t_element data;

    memset(&data, 0, sizeof(t_element));
    if (parsing(&data, ac, av) == 1)
        return 1;
    data_init(&data);
    data.start_time = get_time();
    thread_create(&data);
    supervisor(&data);
    return 0;
}