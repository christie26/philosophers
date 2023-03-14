/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 20:37:40 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/14 18:46:32 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	get_argument(int ac, char **av, t_argv *arg)
{
	struct timeval	start;

	ft_err_msg(ac != 5 && ac != 6, "Invalid argument number !", __FILE__, __LINE__);
	arg->num = ft_atoi(av[1]);
	arg->die = ft_atoi(av[2]);
	arg->eat = ft_atoi(av[3]);
	arg->sleep = ft_atoi(av[4]);
	if (ac == 6)
		arg->must = ft_atoi(av[5]);
	gettimeofday(&start, 0);
	arg->start_time = start;
}

int	ft_create_thread(t_argv arg, t_philo *philo, t_fork **f_ptr)
{
	int	i;
	t_fork	*fork;
	pthread_mutex_t	file;

	fork = *f_ptr;
	pthread_mutex_init(&file, 0);
	i = 0;
	while (i < arg.num)
	{
		philo[i].id = i + 1;
		philo[i].arg = &arg;
		philo[i].left = &fork[i];
		philo[i].right = &fork[(i + 1) % arg.num];
		philo[i].ate = get_time();
		philo[i].file = &file;
		i++;
	}
	i = 0;
	while (i < arg.num)
	{
		pthread_create(&philo[i].t_id, NULL, &each_philo, (&philo[i]));
		i++;
	}
	return (0);
}
