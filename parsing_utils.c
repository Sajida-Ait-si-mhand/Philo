/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/09 01:25:38 by amarzaq           #+#    #+#             */
/*   Updated: 2024/12/10 04:34:26 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
		i++;
	return (i);
}

int	print_error(void)
{
	printf("wrong arguments number!! you need to provide:\n");
	printf("number_of_philosophers\ntime_to_die (in milliseconds)\ntime_to_eat (in milliseconds)\n");
	printf("time_to_sleep (in milliseconds)\nnumber_of_times_each_philosopher_must_eat (optional)\n");
		
	return (1);
}
