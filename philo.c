/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 05:03:01 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/13 05:46:33 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_mutex_destory(pthread_mutex_t *mutix_array, int last_index)
{
	int	i;

	i = 0;
	while (i < last_index)
	{
		pthread_mutex_destroy(&mutix_array[i]);
		i++;
	}
	free(mutix_array);
}

void	free_resources(t_element *data)
{
	if (data->alive_mutex)
		pthread_mutex_destroy(data->alive_mutex);
	if (data->print)
		pthread_mutex_destroy(data->print);
	if (data->forks)
		ft_mutex_destory(data->forks, data->number_of_philosophers);
	if (data->philo_data)
		ft_mutex_destory(data->philo_data, data->number_of_philosophers);
	free(data->philos);
	free(data->print);
	free(data->alive_mutex);
}

pthread_mutex_t	*philo_data_init(t_element *data)
{
	pthread_mutex_t	*philo_data;
	int				i;

	i = 0;
	philo_data = malloc(sizeof(pthread_mutex_t) * data->number_of_philosophers);
	if (!philo_data)
		return (NULL);
	memset(philo_data, 0, sizeof(pthread_mutex_t)
		* data->number_of_philosophers);
	while (i < data->number_of_philosophers)
	{
		if (pthread_mutex_init(&philo_data[i], NULL) != 0)
			return (ft_mutex_destory(philo_data, i), NULL);
		i++;
	}
	return (philo_data);
}

int	main(int ac, char *av[])
{
	t_element	data;
	int			i;

	i = 0;
	memset(&data, 0, sizeof(t_element));
	if (parsing(&data, ac, av) == 1)
		return (1);
	if (data_init(&data) == 1)
		return (1);
	data.start_time = get_time();
	if (threads_creation(&data))
		return (set_alive_false(&data, -1), free_resources(&data), 1);
	supervisor(&data);
	while (i < data.number_of_philosophers)
	{
		if (data.philos[i].thread_id)
			pthread_join(data.philos[i].thread_id, NULL);
		i++;
	}
	free_resources(&data);
	return (0);
}
