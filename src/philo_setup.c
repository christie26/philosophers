/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:37:40 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/10 21:05:08 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	get_argument(int ac, char **av, t_argv *arg)
{
	struct timeval	mytime;

	ft_err_msg(ac != 5 && ac != 6, "Invalid argument number !", __FILE__, __LINE__);
	arg->num = ft_atoi(av[1]);
	arg->die = ft_atoi(av[2]);
	arg->eat = ft_atoi(av[3]);
	arg->sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->must = ft_atoi(av[5]);
	gettimeofday(&mytime, 0);
	arg->start_time = mytime.tv_usec;
}

int	create_thread(t_argv arg, t_philo *philo, t_fork **f_ptr)
{
	int	i;
	t_fork	*fork;

	fork = *f_ptr;
	i = 0;
	while (i < arg.num)
	{
		pthread_mutex_init(fork[i].mutex, 0);
		i++;
	}
	i = 0;
	while (i < arg.num)
	{
		philo[i].id = i;
		philo[i].arg = &arg;
		philo[i].left = &fork[i];
		if (i == arg.num - 1)
			philo[i].right = &fork[0];
		else
			philo[i].right = &fork[i + 1];
	//	philo[i].file = &file;
		pthread_create(&philo[i].t_id, NULL, &each_philo, (&philo[i]));
		i++;
	}
	return (0);
}
