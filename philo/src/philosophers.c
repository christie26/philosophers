#include "../include/philo.h"

void *each_philo(void *data)
{
	t_argv	*arg;
	t_philo	philo;

	arg = (t_argv*)(data);
	philo = arg->philo[arg->idx];

	philo.status = 1;
	printf("I am %dth philosophers\n", arg->idx);
	return ((void *)(long)(arg->idx));
}
