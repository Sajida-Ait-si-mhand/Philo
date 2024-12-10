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

typedef struct s_philo {
	int				id;
	int				n_of_meals;
	unsigned long		last_meal;
};

typedef struct s_element
{
	int number_of_philosophers;
	int time_to_die;
	int time_to_eat;
	int time_to_sleep;
	int n_of_meals;
	bool hp;
	pthread_t *philos;
	pthread_mutex_t *philo_data;
	pthread_mutex_t *forks;
	pthread_mutex_t *print;
	pthread_mutex_t *hp_mutex;
} t_element;

// PARSING

int	parsing(t_element *data, int ac, char **av);
int	ft_strlen(char *str);
int	print_error(void);
unsigned long get_time(void);
unsigned long get_time(void);
#endif