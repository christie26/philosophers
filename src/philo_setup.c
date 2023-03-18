/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:37:40 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/18 15:31:50 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	get_argument(int ac, char **av, t_argv *arg)
{
	struct timeval	start;

	ft_err_msg(ac != 5 && ac != 6, "Invalid argument number !", 0, 0);
	arg->num = ft_atoi(av[1]);
	arg->die = ft_atoi(av[2]);
	arg->eat = ft_atoi(av[3]);
	arg->sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->must = ft_atoi(av[5]);
	gettimeofday(&start, 0);
	arg->start_time = start;
}

int	ft_create_thread(t_argv arg, t_philo *philo, t_fork *fork)
{
	int				i;
	pthread_mutex_t	write;

	i = -1;
	while (++i < arg.num)
	{
		pthread_mutex_init(&fork[i].mutex, 0);
		fork[i].fork = 0;
	}
	pthread_mutex_init(&write, 0);
	pthread_mutex_init(&arg.dead.mutex, 0);
	arg.dead.flag = 0;
	arg.write = write;
	i = -1;
	while (++i < arg.num)
	{
		philo[i].id = i + 1;
		philo[i].arg = &arg;
		philo[i].left = &fork[i];
		philo[i].right = &fork[(i + 1) % arg.num];
		philo[i].ate = get_time();
	}
	i = -1;
	while (++i < arg.num)
		pthread_create(&philo[i].t_id, NULL, &each_philo, (&philo[i]));
	return (0);
}
