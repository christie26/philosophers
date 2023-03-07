#include "../philo.h"

int	main(int ac, char **av)
{
	printf("Philo starts\n");
	printf("ac = %d\n", ac);
	int i = 0;
	while (av[i])
	{
		printf("av[%d] = %s\n", i, av[i]);
		i++;
	}
	return (0);
}
