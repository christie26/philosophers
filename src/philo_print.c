/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:29:13 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/18 16:01:56 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_print(t_philo *philo, char *message)
{
	int		time;

	pthread_mutex_lock(&philo->arg->write);
	time = time_stamp(philo->arg->start_time);
	if (philo_dead(philo, 0))
	{
		if (!message)
			printf("%d %d %s\n", time, philo->id, "died");
		pthread_mutex_unlock(&philo->arg->write);
		return ;
	}
	else 
	{
		printf("%d %d %s\n", time, philo->id, message);
		pthread_mutex_unlock(&philo->arg->write);
	}
}

int	philo_dead(t_philo *philo, int flag)
{
	if (flag)
	{
		pthread_mutex_lock(&philo->arg->dead.mutex);
		philo->arg->dead.flag = 1;
		pthread_mutex_unlock(&philo->arg->dead.mutex);
		return (1);
	}
	else
	{
		pthread_mutex_lock(&philo->arg->dead.mutex);
		if (philo->arg->dead.flag)
		{
			pthread_mutex_unlock(&philo->arg->dead.mutex);
			return (1);
		}
		else
		{
			pthread_mutex_unlock(&philo->arg->dead.mutex);
			return (0);
		}
	}
}
