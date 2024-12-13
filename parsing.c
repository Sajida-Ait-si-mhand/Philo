/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 05:02:39 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/13 05:33:02 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

char	*ft_strndup(char *str, int n)
{
	int		len;
	char	*str_copy;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	len = ft_strlen(str);
	str_copy = malloc(sizeof(char) * (len + 1));
	if (!str_copy)
	{
		write(2, "malloc failed\n", ft_strlen("malloc failed\n"));
		return (NULL);
	}
	while (str[i] && i < n)
	{
		str_copy[i] = str[i];
		i++;
	}
	str_copy[i] = '\0';
	return (str_copy);
}

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

char	*trim(char *str)
{
	int	start;
	int	end;
	int	len;

	if (!str)
		return (NULL);
	start = 0;
	len = ft_strlen(str);
	end = len - 1;
	while (str[start] && is_space(str[start]))
		start++;
	while (str[end] && is_space(str[end]) && end >= start)
		end--;
	return (ft_strndup(str + start, end - start + 1));
}

long	custom_atoi(char *number_string)
{
	char			*number;
	int				i;
	unsigned int	num;

	number = trim(number_string);
	if (!number)
		return (-1);
	num = 0;
	i = 0;
	while (number[i])
	{
		if (number[i] < '0' || number[i] > '9')
		{
			free(number);
			return (-1);
		}
		num *= 10;
		num += number[i] - '0';
		i++;
	}
	free(number);
	return (num);
}

int	parsing(t_element *data, int ac, char **av)

{
	int	error_code;

	if (ac < 5 || ac > 6)
		return (print_error());
	data->number_of_philosophers = custom_atoi(av[1]);
	data->time_to_die = custom_atoi(av[2]);
	data->time_to_eat = custom_atoi(av[3]);
	data->time_to_sleep = custom_atoi(av[4]);
	if (ac == 6)
		data->n_of_meals = custom_atoi(av[5]);
	else
		data->n_of_meals = -1;
	error_code = (data->number_of_philosophers == -1
			|| (int)data->time_to_die == -1 || data->time_to_eat == -1
			|| data->time_to_sleep == -1
			|| (ac == 6 && data->n_of_meals == -1));
	if (data->number_of_philosophers <= 0 || (data->n_of_meals <= 0 && ac == 6)
		|| error_code)
	{
		write(2, "invalid arguments\n", ft_strlen("invalid arguments\n"));
		return (1);
	}
	return (0);
}
