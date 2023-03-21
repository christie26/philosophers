/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:37:40 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/21 22:31:40 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	get_argument(int ac, char **av, t_argv *arg)
{
	struct timeval	start;

	if (ft_err_msg(ac != 5 && ac != 6, "Invalid argument number !"))
		return (1);
	arg->num = ft_atoi(av[1]);
	arg->die = ft_atoi(av[2]);
	arg->eat = ft_atoi(av[3]);
	arg->sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->must = ft_atoi(av[5]);
	if (ft_err_msg((!arg->num || !arg->die || !arg->eat || !arg->sleep), \
				"Invalid argument value !"))
		return (1);
	if (ac == 6 && ft_err_msg(!arg->must, "Invalid argument value !"))
		return (1);
	gettimeofday(&start, 0);
	arg->start_time = start;
	arg->option = ac - 5;
	return (0);
}

void	philo_set(t_argv *arg, t_philo **philo, t_fork *fork)
{
	int	i;

	i = -1;
	while (++i < arg->num)
	{
		(*philo)[i].id = i + 1;
		(*philo)[i].arg = arg;
		(*philo)[i].left = &fork[i];
		(*philo)[i].right = &fork[(i + 1) % arg->num];
		(*philo)[i].status = 1;
		(*philo)[i].time = 0;
	}
}

int	ft_fork_init(t_fork **ptr, int num)
{
	t_fork	*fork;
	int		i;

	fork = *ptr;
	i = -1;
	while (++i < num)
	{
		if (pthread_mutex_init(&fork[i].mutex, 0))
			return (1);
		fork[i].status = 0;
	}
	return (0);
}

int	ft_create_thread(t_argv *arg, t_philo **philo, t_fork **fork)
{
	int				i;
	int				flag;
	pthread_mutex_t	write;
	pthread_mutex_t	dead;
	int				ready_num;
	pthread_mutex_t	ready;

	if (ft_err_msg(pthread_mutex_init(&write, 0), "Fail mutex_init"))
		return (1);
	if (ft_err_msg(pthread_mutex_init(&dead, 0), "Fail mutex_init"))
		return (1);
	if (ft_err_msg(pthread_mutex_init(&ready, 0), "Fail mutex_init"))
		return (1);
	ready_num = 0;
	arg->ready_num = &ready_num;
	arg->write = &write;
	arg->dead = &dead;
	flag = 0;
	arg->flag = &flag;
	arg->ready = &ready;
	philo_set(arg, philo, *fork);
	i = -1;
	while (++i < arg->num)
	{
		if (ft_err_msg(pthread_create(&(*philo)[i].t_id, 0, \
						&each_philo, (&(*philo)[i])), "Fail pthread_create"))
			return (1);
		usleep(100);
	}
	return (0);
}
