/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 05:02:32 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/13 05:02:34 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*forks_init(t_element *data)
{
	pthread_mutex_t	*forks;
	int				i;

	i = -1;
	forks = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!forks)
		return (NULL);
	memset(forks, 0, sizeof(pthread_mutex_t) * data->number_of_philosophers);
	while (++i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			ft_mutex_destory(forks, i);
			return (NULL);
		}
	}
	return (forks);
}

pthread_mutex_t	*print_init(void)
{
	pthread_mutex_t	*print;

	print = malloc(sizeof(pthread_mutex_t));
	if (!print)
		return (NULL);
	if (pthread_mutex_init(print, NULL) != 0)
	{
		return (ft_mutex_destory(print, 1), NULL);
	}
	return (print);
}

pthread_mutex_t	*alive_mutex_init(void)
{
	pthread_mutex_t	*alive_mutex;

	alive_mutex = malloc(sizeof(pthread_mutex_t));
	if (!alive_mutex)
		return (NULL);
	if (pthread_mutex_init(alive_mutex, NULL) != 0)
		return (ft_mutex_destory(alive_mutex, 1), NULL);
	return (alive_mutex);
}
