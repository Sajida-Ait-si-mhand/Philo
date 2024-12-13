/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 05:02:54 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/13 05:13:33 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_alive_false(t_element *data, int index)
{
	pthread_mutex_lock(data->print);
	pthread_mutex_lock(data->alive_mutex);
	data->alive = false;
	pthread_mutex_unlock(data->alive_mutex);
	if (index != -1)
		printf("%lu %u died\n", get_time() - data->start_time, index + 1);
	pthread_mutex_unlock(data->print);
}

bool	ft_alive(t_element *data)
{
	bool	alive;

	pthread_mutex_lock(data->alive_mutex);
	alive = data->alive;
	pthread_mutex_unlock(data->alive_mutex);
	return (alive);
}

int	printf_mutix(unsigned long time, int id, t_element *data, char *str)
{
	pthread_mutex_lock(data->print);
	if (ft_alive(data) == false)
	{
		pthread_mutex_unlock(data->print);
		return (1);
	}
	printf("%lu %d %s", time - data->start_time, id + 1, str);
	pthread_mutex_unlock(data->print);
	return (0);
}

unsigned long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(unsigned long time)
{
	unsigned long	start;
	unsigned long	long_time;
	unsigned long	short_time;

	long_time = time * 0.8;
	short_time = time * 0.2;
	usleep(long_time * 1000);
	start = get_time();
	while (get_time() - start < short_time)
		usleep(500);
}
