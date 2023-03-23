/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:54:43 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/21 22:27:12 by yoonsele         ###   ########.fr       */
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
	int				option;
	int				num;
	int				die;
	int				eat;
	int				sleep;
	int				must;
	struct timeval	start_time;
	pthread_mutex_t	write;
	pthread_mutex_t	dead;
	pthread_mutex_t	ready;
	int				*ready_num;
	int				*flag;
}	t_argv;

typedef struct s_fork {
	pthread_mutex_t	mutex;
	int				status;
}	t_fork;

typedef struct s_philo {
	int				id;
	int				status;
	int				time;
	struct timeval	ate;
	pthread_t		t_id;
	t_argv			*arg;
	t_fork			*left;
	t_fork			*right;
}	t_philo;

// set-up
int				get_argument(int ac, char **av, t_argv *arg);
int				ft_fork_init(t_fork **ptr, int num);
int				ft_create_thread(t_argv *arg, t_philo **philo, t_fork **fork);

// utils
int				ft_strlen(char *str);
int				ft_atoi(char *str);
int				ft_error(int condition, char *error_message);
struct timeval	ft_get_time(void);
int				time_stamp(struct timeval start);
int				ft_usleep2(t_philo *philo, int time);
int				ft_usleep1(t_philo *philo, int time);

// philo
void			*each_philo(void *data);
int				take_lfork(t_philo *philo);
int				take_rfork(t_philo *philo);
int				ft_check_dead(t_philo *philo);
void			philo_dead(t_philo *philo);
void			philo_print(t_philo *philo, char *message);
void			philo_wait(t_philo *philo);

#endif
