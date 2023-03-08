#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo {
	int		idx;
	int		food;
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
int	ft_atoi(const char *str);
int	ft_strlen(char *str);

void	ft_putchar_fd(char c, int fd);
void	ft_putstr_fd(char *str, int fd);
void	ft_putendl_Fd(char *str, int fd);
void	ft_err_msg(int condition, char *error_message, char *file, int line);
void	ft_err_sys(int condition, char *file, int line);

#endif
