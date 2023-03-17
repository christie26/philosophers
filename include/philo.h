/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:54:43 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/17 11:45:41 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <stdio.h>

# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIED 4

typedef struct s_argv {
	int				num;
	int				die;
	int				eat;
	int				sleep;
	int				must;
	struct timeval	start_time;
	pthread_mutex_t	write;
}	t_argv;

typedef struct s_fork {
	pthread_mutex_t	mutex;
	int				fork;
}	t_fork;

typedef struct s_philo {
	int				id;
	int				status;
	struct timeval	ate;
	pthread_t		t_id;
	t_argv			*arg;
	t_fork			*left;
	t_fork			*right;
}	t_philo;

// set-up
void	get_argument(int ac, char **av, t_argv *arg);
int		ft_create_thread(t_argv arg, t_philo *philo, t_fork *fork);

//utils
int				ft_strlen(char *str);
int				ft_atoi(const char *str);
void			ft_err_msg(int condition, char *error_message, char *file, int line);
void			ft_err_sys(int condition, char *file, int line);
struct timeval	get_time(void);
int				time_stamp(struct timeval start);

void	*each_philo(void *data);
void	philo_print(t_philo *philo, int status);

#endif
