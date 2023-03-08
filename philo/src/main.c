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
	pthread_t	*thread;
	t_philo		*philo;
    int 		status;
	int			i;
	
	if (check_input(ac, av, &arg))
		return (1);
	
	thread = (pthread_t *)malloc(sizeof(pthread_t) * arg.num);
	philo = (t_philo *)malloc(sizeof(t_philo) * arg.num);
	i = -1;
	while (i++ < arg.num)
		memset(&philo[i], 0, sizeof(t_philo));

	arg.philo = philo;
	i = 0;
	while (i < arg.num)
	{
		arg.idx = i;
    	pthread_create(&thread[i], NULL, each_philo, (void *)(&arg));
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
