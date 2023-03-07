#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>

typedef struct s_argv {
	int	philo;
	int	die;
	int	eat;
	int	sleep;
	int	must;
}	t_argv;


//utils
int	ft_atoi(const char *str);


#endif
