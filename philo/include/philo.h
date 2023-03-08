#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>

# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIED 4

typedef struct s_philo {
	int	status;
	int	count;
}	t_philo;

typedef struct s_argv {
	int		num;
	int		die;
	int		eat;
	int		sleep;
	int		must;
	int		start_time;
	int		idx;
	t_philo	*philo;
}	t_argv;

//utils
int		ft_atoi(const char *str);
void	ft_err_msg(int condition, char *error_message, char *file, int line);
void	ft_err_sys(int condition, char *file, int line);
int		what_time(t_argv arg);

void	*each_philo(void *data);

#endif
