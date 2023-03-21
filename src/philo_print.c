/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:29:13 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/21 15:41:23 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_print(t_philo *philo, char *message)
{
	int			time;
	static int	die;

	pthread_mutex_lock(philo->arg->write);
	time = time_stamp(philo->arg->start_time);
	if (!message)
	{
		if (die == 0)
			printf("%d %d %s\n", time, philo->id, "died");
		die = 1;
		pthread_mutex_unlock(philo->arg->write);
		return ;
	}
	if (!philo_dead(philo, 0))
		printf("%d %d %s\n", time, philo->id, message);
	pthread_mutex_unlock(philo->arg->write);
}

void	philo_sleep_think(t_philo *philo)
{
	philo_print(philo, "is sleeping");
	usleep(philo->arg->sleep * 1000);
	philo->status = SLEEP;
	if (philo_dead(philo, 0))
		return ;
	philo_print(philo, "is thinking");
	philo->status = THINK;
}

int	philo_dead(t_philo *philo, int flag)
{
	if (flag)
	{
		pthread_mutex_lock(philo->arg->dead);
		*philo->arg->flag = 1;
		pthread_mutex_unlock(philo->arg->dead);
		usleep(100);
		philo_print(philo, 0);
		philo->status = DIED;
		return (1);
	}
	else
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
}
