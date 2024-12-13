/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 05:03:08 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/13 05:47:07 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	if (printf_mutix(get_time(), philo->id, philo->data, "has taken a fork\n"))
		return (pthread_mutex_unlock(&philo->data->forks[philo->left_fork]), 1);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	if (printf_mutix(get_time(), philo->id, philo->data, "has taken a fork\n"))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return (1);
	}
	if (printf_mutix(get_time(), philo->id, philo->data, "is eating\n"))
	{
		pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
		return (1);
	}
	pthread_mutex_lock(&philo->data->philo_data[philo->id]);
	philo->last_meal = get_time();
	philo->n_of_meals++;
	pthread_mutex_unlock(&philo->data->philo_data[philo->id]);
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	return (0);
}

void	one_philo(t_philo *philo)
{
	if (philo->data->number_of_philosophers == 1)
	{
		pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
		printf_mutix(get_time(), philo->id, philo->data, "has taken a fork\n");
		while (ft_alive(philo->data) == false)
			;
		pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	}
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->number_of_philosophers == 1)
		return (one_philo(philo), NULL);
	pthread_mutex_lock(philo->data->philo_data + philo->id);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->data->philo_data + philo->id);
	if (philo->id % 2 != 0)
		usleep(500);
	while (1)
	{
		if (eating(philo))
			return (NULL);
		if (printf_mutix(get_time(), philo->id, philo->data, "is sleeping\n"))
			return (NULL);
		ft_usleep(philo->data->time_to_sleep);
		if (printf_mutix(get_time(), philo->id, philo->data, "is thinking\n"))
			return (NULL);
		usleep(200);
	}
	return (NULL);
}
