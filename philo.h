/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saait-si <saait-si@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 05:29:58 by saait-si          #+#    #+#             */
/*   Updated: 2024/12/13 05:29:59 by saait-si         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <pthread.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo	t_philo;
typedef struct s_element
{
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_of_meals;
	unsigned long		start_time;
	bool				alive;
	t_philo				*philos;
	pthread_mutex_t		*philo_data;
	pthread_mutex_t		*forks;
	pthread_mutex_t		*print;
	pthread_mutex_t		*alive_mutex;
}						t_element;

typedef struct s_philo
{
	int					id;
	unsigned int		left_fork;
	unsigned int		right_fork;
	int					n_of_meals;
	unsigned long		last_meal;
	pthread_t			thread_id;
	t_element			*data;
}						t_philo;

// 🌸     PARSING    🌸

char					*ft_strndup(char *str, int n);
int						is_space(char c);
char					*trim(char *str);
long					my_atoi(char *number_string);
int						parsing(t_element *data, int ac, char **av);

// ⁴⁰⁴ ERROR ⁴⁰⁴
int						print_error(void);

// 📢  INITIALIZATION 📢

pthread_mutex_t			*philo_data_init(t_element *data);
pthread_mutex_t			*alive_mutex_init(void);
pthread_mutex_t			*forks_init(t_element *data);
pthread_mutex_t			*print_init(void);
t_philo					*philos_init(t_element *data);
int						data_init(t_element *data);

// 🧶 TREADS_CREATION 🧶

unsigned long			get_time(void);
int						threads_creation(t_element *data);

// 🔁 ROUTINE 🔁
void					*routine(void *arg);
int						eating(t_philo *philo);
void					one_philo(t_philo *philo);
bool					ft_alive(t_element *data);
int						supervisor(t_element *data);
void					set_alive_false(t_element *data, int index);
int						printf_mutix(unsigned long time, int id,
							t_element *data, char *str);

// 🔨 utils 🔨
void					ft_usleep(unsigned long time);
int						ft_strlen(char *str);

// 💀 kill 💀
void					ft_kill_threads(t_element *data, int last_index);
void					ft_mutex_destory(pthread_mutex_t *mutix_array,
							int last_index);

// free
void					free_resources(t_element *data);

#endif