/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:49:47 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/18 15:19:45 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	main(int ac, char **av)
{
	t_argv	arg;
	t_philo	*philo;
	t_fork	*fork;
	int		i;

	get_argument(ac, av, &arg);
	philo = (t_philo *)malloc(sizeof(t_philo) * arg.num);
	fork = (t_fork *)malloc(sizeof(t_fork) * arg.num * 2);
	ft_create_thread(arg, philo, fork);
	i = 0;
	while (i < arg.num)
	{
		pthread_join(philo[i].t_id, 0);
		i++;
	}
	i = 0;
	while (i < arg.num)
	{
		pthread_mutex_destroy(&fork[i].mutex);
		i++;
	}
	return (0);
}
