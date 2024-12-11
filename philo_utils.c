#include "philo.h"

void set_alive_false(t_element *data)
{
	pthread_mutex_lock(data->alive_mutex);
	data->alive = false;
	pthread_mutex_unlock(data->alive_mutex);
}

bool ft_alive(t_element *data)
{
	bool alive;

	pthread_mutex_lock(data->alive_mutex);
	alive = data->alive;
	pthread_mutex_unlock(data->alive_mutex);
	return (alive);
}

unsigned long get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void ft_usleep(unsigned long time)
{
	unsigned long start;

	start = get_time();
	while (get_time() - start < time)
		usleep(500);
}