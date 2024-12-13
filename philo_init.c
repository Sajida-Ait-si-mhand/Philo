/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 05:02:48 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/13 05:08:40 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_kill_threads(t_element *data, int last_index)
{
	int	i;

	i = 0;
	while (i < last_index)
	{
		pthread_join(data->philos[i].thread_id, NULL);
		i++;
	}
}

int	threads_creation(t_element *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		data->philos[i].last_meal = get_time();
		if (pthread_create(&data->philos[i].thread_id, NULL, routine,
				&data->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

t_philo	*philos_init(t_element *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = malloc(sizeof(t_philo) * data->number_of_philosophers);
	if (!philo)
		return (NULL);
	memset(philo, 0, sizeof(t_philo) * data->number_of_philosophers);
	while (++i < data->number_of_philosophers)
	{
		philo[i].id = i;
		if (i % 2 == 0)
		{
			philo[i].left_fork = i;
			philo[i].right_fork = (i + 1) % data->number_of_philosophers;
		}
		else
		{
			philo[i].left_fork = (i + 1) % data->number_of_philosophers;
			philo[i].right_fork = i;
		}
		philo[i].n_of_meals = 0;
		philo[i].data = data;
	}
	return (philo);
}

int	data_init(t_element *data)
{
	data->alive = true;
	data->alive_mutex = alive_mutex_init();
	data->philo_data = philo_data_init(data);
	data->forks = forks_init(data);
	data->print = print_init();
	data->philos = philos_init(data);
	if (!data->philos || !data->philo_data || !data->forks || !data->print
		|| !data->alive_mutex)
		return (free_resources(data), 1);
	return (0);
}
