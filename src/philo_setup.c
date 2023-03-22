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
	if (ft_error(ac != 5 && ac != 6, "Invalid argument number !"))
		return (1);
	arg->num = ft_atoi(av[1]);
	arg->die = ft_atoi(av[2]);
	arg->eat = ft_atoi(av[3]);
	arg->sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->must = ft_atoi(av[5]);
	if (ft_error((!arg->num || !arg->die || !arg->eat || !arg->sleep), \
				"Invalid argument value !"))
		return (1);
	if (ac == 6 && ft_error(!arg->must, "Invalid argument value !"))
		return (1);
	arg->start_time = ft_get_time();
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
	int				ready_num;

	if (ft_error(pthread_mutex_init(&arg->write, 0), "Fail mutex_init"))
		return (1);
	if (ft_error(pthread_mutex_init(&arg->dead, 0), "Fail mutex_init"))
		return (1);
	if (ft_error(pthread_mutex_init(&arg->ready, 0), "Fail mutex_init"))
		return (1);
	ready_num = 0;
	arg->ready_num = &ready_num;
	flag = 0;
	arg->flag = &flag;
	philo_set(arg, philo, *fork);
	i = -1;
	while (++i < arg->num)
	{
		if (ft_error(pthread_create(&(*philo)[i].t_id, 0, \
						&each_philo, (&(*philo)[i])), "Fail pthread_create"))
			return (1);
		usleep(300);
	}
	return (0);
}
