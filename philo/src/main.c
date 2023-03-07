#include "../philo.h"

int	check_input(int ac, char **av, t_argv *arg)
{
	if (ac != 5 && ac != 6)
	{
		printf("Invalid arguments\n");
		return (1);
	}
	arg->philo = ft_atoi(av[1]);
	arg->die = ft_atoi(av[2]);
	arg->eat = ft_atoi(av[3]);
	arg->sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->must = ft_atoi(av[5]);

	// want to print arguments ?
	printf("number_of_philosophers: %d\n", arg->philo);
	printf("time_to_die (in milliseconds): %d\n", arg->die);
	printf("time_to_eat (in milliseconds): %d\n", arg->eat);
	printf("time_to_sleep (in milliseconds): %d\n", arg->sleep);
	if (ac == 6)
		printf("number_of_times_each_philosopher_must_eat: %d\n", arg->must);
	return (0);
}


int	main(int ac, char **av)
{
	t_argv	arg;

	if (check_input(ac, av, &arg))
		return (1);

	return (0);
}
