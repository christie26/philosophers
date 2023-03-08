#include "../include/philo.h"

int	check_input(int ac, char **av, t_argv *arg)
{
	struct timeval mytime;

	if (ac != 5 && ac != 6)
	{
		printf("Invalid arguments\n");
		return (1);
	}
	arg->num = ft_atoi(av[1]);
	arg->die = ft_atoi(av[2]);
	arg->eat = ft_atoi(av[3]);
	arg->sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->must = ft_atoi(av[5]);
	gettimeofday(&mytime, 0);
	arg->start_time = mytime.tv_usec;
/*
	// want to print arguments ?
	printf("number_of_philosophers: %d\n", arg->philo);
	printf("time_to_die (in milliseconds): %d\n", arg->die);
	printf("time_to_eat (in milliseconds): %d\n", arg->eat);
	printf("time_to_sleep (in milliseconds): %d\n", arg->sleep);
	if (ac == 6)
		printf("number_of_times_each_philosopher_must_eat: %d\n", arg->must);
*/
	return (0);
}

void *each_philo(void *data)
{
	t_argv	*arg;
	t_philo	philo;

	arg = (t_argv*)(data);
	philo = arg->philo[arg->idx];
	
	philo.food = arg->idx;
	printf("I am %dth philosophers\n", arg->idx);
	return ((void *)(long)(arg->idx));
}

void	what_time(t_argv arg)
{
	struct timeval cur;
	gettimeofday(&cur, 0);

	printf("rn it's %d\n", cur.tv_usec - arg.start_time);

}

int	main(int ac, char **av)
{
	t_argv		arg;
	pthread_t	*thread;
	t_philo		*philo;
    int status;
	
	if (check_input(ac, av, &arg))
		return (1);
	
	thread = (pthread_t *)malloc(sizeof(pthread_t) * arg.num);
	philo = (t_philo *)malloc(sizeof(t_philo) * arg.num);
	int i = 0;
	arg.philo = philo;
	while (i < arg.num)
	{
		arg.idx = i;
    	pthread_create(&thread[i], NULL, each_philo, (void *)(&arg));
		what_time(arg);
		i++;
	}

	i = 0;
	while (i < arg.num)
	{
		pthread_join(thread[i], (void **)&status);
		printf("%dth thread End\n", status);
		i++;
	}

	return (0);
}
