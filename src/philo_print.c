/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:29:13 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/21 22:30:25 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_print(t_philo *philo, char *message)
{
	if (message == 0)
	{
		pthread_mutex_lock(philo->arg->dead);
		if (*philo->arg->flag == 0)
		{
			*philo->arg->flag = 1;
			pthread_mutex_unlock(philo->arg->dead);
			pthread_mutex_lock(philo->arg->write);
			printf("%d %d %s\n", time_stamp(philo->arg->start_time), \
					philo->id, "died");
			pthread_mutex_unlock(philo->arg->write);
		}
		else
			pthread_mutex_unlock(philo->arg->dead);
		return ;
	}
	if (ft_check_dead(philo))
		return ;
	pthread_mutex_lock(philo->arg->write);
	printf("%d %d %s\n", time_stamp(philo->arg->start_time), philo->id, message);
	pthread_mutex_unlock(philo->arg->write);
}

int	philo_sleep_think(t_philo *philo)
{
	if (ft_check_dead(philo))
		return (1);
	philo_print(philo, "is sleeping");
	ft_usleep(philo->arg->sleep * 1000);
	philo->status = SLEEP;
	if (ft_check_dead(philo))
		return (1);
	philo_print(philo, "is thinking");
	philo->status = THINK;
	return (0);
}

int	philo_dead(t_philo *philo)
{
	philo_print(philo, 0);
	philo->status = DIED;
	return (1);
}

int	ft_check_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->arg->dead);
	if (*philo->arg->flag)
	{
		pthread_mutex_unlock(philo->arg->dead);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(philo->arg->dead);
		return (0);
	}
}
