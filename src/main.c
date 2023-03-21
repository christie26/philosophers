/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:49:47 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/21 22:28:54 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_clear_thread_mutex(t_argv *arg, t_philo **philo, t_fork **fork)
{
	int		i;
	long	tmp;

	i = 0;
	tmp = 0;
	while (i < arg->num)
	{
		if (ft_err_msg(pthread_join((*philo)[i].t_id, (void *)tmp), "F: join"))
			return (1);
		i++;
	}
	i = 0;
	while (i < arg->num)
	{
		if (ft_err_msg(pthread_mutex_destroy(&(*fork)[i].mutex), "Fail m_des1"))
			return (1);
		i++;
	}
	if (ft_err_msg(pthread_mutex_destroy(arg->write), "Fail p_m_destroy2"))
		return (1);
	if (ft_err_msg(pthread_mutex_destroy(arg->dead), "Fail p_m_destroy3"))
		return (1);
	if (ft_err_msg(pthread_mutex_destroy(arg->ready), "Fail p_m_destroy4"))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_argv	arg;
	t_philo	*philo;
	t_fork	*fork;

	if (get_argument(ac, av, &arg))
		return (1);
	philo = (t_philo *)malloc(sizeof(t_philo) * arg.num);
	if (ft_err_msg(!philo, "Fail to malloc()"))
		return (1);
	fork = (t_fork *)malloc(sizeof(t_fork) * arg.num);
	if (ft_err_msg(!fork, "Fail to malloc()"))
		return (1);
	if (ft_err_msg(ft_fork_init(&fork, arg.num), "Fail p_m_init"))
		return (1);
	if (ft_create_thread(&arg, &philo, &fork))
		return (1);
	if (ft_clear_thread_mutex(&arg, &philo, &fork))
		return (1);
	return (0);
}
