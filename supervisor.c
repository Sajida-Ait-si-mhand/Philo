#include "philo.h"


void supervisor(t_element *data)
{
    int i;
     int philos_done_eating;

    while (ft_alive(data) == true)
    {
        i = -1;
        philos_done_eating = 0;
        while (++i < data->number_of_philosophers)
        {
            pthread_mutex_lock(&data->philo_data[i]);
            if (get_time() - data->philos[i].last_meal > (unsigned long) data->time_to_die)
            {
                printf_mutix(i, data, "died\n");
                set_alive_false(data);
                pthread_mutex_unlock(&data->philo_data[i]);
                return ;
            }
            if (data->philos[i].n_of_meals >= data->n_of_meals)
                philos_done_eating++;
            pthread_mutex_unlock(&data->philo_data[i]);
        }
        if (philos_done_eating == data->number_of_philosophers)
            set_alive_false(data);
    }
}