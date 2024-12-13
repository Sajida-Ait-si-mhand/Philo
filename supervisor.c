/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   supervisor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 05:03:14 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/13 05:19:43 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philosopher_death(t_element *data, uint64_t i)
{
	unsigned long	time_since_last_meal;

	time_since_last_meal = get_time() - data->philos[i].last_meal;
	if (time_since_last_meal > (unsigned long)data->time_to_die)
	{
		set_alive_false(data, i);
		return (1);
	}
	return (0);
}

int	supervisor(t_element *data)
{
	uint32_t	philos_done_eating;
	uint64_t	i;

	while (ft_alive(data))
	{
		i = -1;
		philos_done_eating = 0;
		while (++i < (uint64_t)data->number_of_philosophers)
		{
			pthread_mutex_lock(data->philo_data + i);
			if (check_philosopher_death(data, i))
			{
				pthread_mutex_unlock(data->philo_data + i);
				return (1);
			}
			if (data->philos[i].n_of_meals >= data->n_of_meals
				&& data->n_of_meals != -1)
				philos_done_eating++;
			pthread_mutex_unlock(data->philo_data + i);
		}
		if (philos_done_eating == (uint32_t)data->number_of_philosophers)
			set_alive_false(data, -1);
	}
	return (0);
}
