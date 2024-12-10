#include "philo.h"

int main(int ac, char **av)
{
	struct timeval	time;
	t_element data;
	parsing(&data, ac, av);

	gettimeofday(&time, NULL);
	printf("mili %ld\n", get_time());

}