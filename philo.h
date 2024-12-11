#ifndef PHILO_H
#define PHILO_H
#include <pthread.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

typedef struct s_philo t_philo;
typedef struct s_element
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int n_of_meals;
	unsigned long start_time;
	bool alive;
	t_philo *philos;
	pthread_mutex_t *philo_data;
	pthread_mutex_t *forks;
	pthread_mutex_t *print;
	pthread_mutex_t *alive_mutex;
} t_element;

typedef struct s_philo {
	int				id;
	unsigned int	left_fork;
	unsigned int	right_fork;
	int				n_of_meals;
	unsigned long		last_meal;
	pthread_t		thread_id;
	t_element		*data;
} t_philo;

// PARSING

int	parsing(t_element *data, int ac, char **av);
int	ft_strlen(char *str);
int	print_error(void);
unsigned long get_time(void);
unsigned long get_time(void);
int thread_create(t_element *data);
void ft_usleep(unsigned long time);
unsigned long get_time(void);
void supervisor(t_element *data);
void set_alive_false(t_element *data);
bool ft_alive(t_element *data);
void  printf_mutix(int id, t_element *data, char *str);
#endif