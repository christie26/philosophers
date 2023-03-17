/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:29:13 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/17 19:43:45 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_print(t_philo *philo, int status)
{
	int		time;
	char	*message;

	pthread_mutex_lock(&philo->arg->write);
	time = time_stamp(philo->arg->start_time);
//	printf("%d a\n", time_stamp(philo->arg->start_time));
	if (philo_dead(philo, 0))
	{
		printf("someone died !\n");
		pthread_mutex_unlock(&philo->arg->write);
		return ;
	}
	else 
	{
		if (status == 1)
			message = "has taken a fork";
		else if (status == 2)
			message = "is eating";
		else if (status == 3)
			message = "is sleeping";
		else if (status == 4)
			message = "is thinking";
		else
			message = "died";
		printf("%d %d %s\n", time, philo->id, message);
		pthread_mutex_unlock(&philo->arg->write);

	}
}

/*
   ◦ timestamp_in_ms X has taken a fork
   ◦ timestamp_in_ms X is eating
   ◦ timestamp_in_ms X is sleeping
   ◦ timestamp_in_ms X is thinking
   ◦ timestamp_in_ms X died
   */
