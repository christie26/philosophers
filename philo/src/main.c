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
	return (0);
}

int	main(int ac, char **av)
{
	t_argv		arg;
	t_philo		*philo;
    int 		status;
	int			i;
	
	if (check_input(ac, av, &arg))
		return (1);
	
	philo = (t_philo *)malloc(sizeof(t_philo) * arg.num);
	arg.philo = philo;
	i = 0;
	while (i < arg.num)
	{
		arg.idx = i;
    	pthread_create(&arg.philo[i].t_id, NULL, each_philo, (void *)(&arg));
		i++;
	}
	i = 0;
	while (i < arg.num)
	{
		pthread_join(arg.philo[i].t_id, (void **)&status);
		printf("%dth thread End\n", status);
		i++;
	}

	return (0);
}
