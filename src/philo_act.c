/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:47:27 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/18 16:01:53 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// 0: get fork
// 1: died
int	wait_fork(t_philo *philo)
{
	while (1)
	{
		if (time_stamp(philo->ate) > philo->arg->die)
			return (1);
		usleep(100);
		pthread_mutex_lock(&philo->left->mutex);
	}
}

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left->mutex);
	philo_print(philo, "has taken a fork");
	pthread_mutex_lock(&philo->right->mutex);
	philo_print(philo, "has taken a fork");
	if (time_stamp(philo->ate) > philo->arg->die)
	{
		philo->status = DIED;
		philo_dead(philo, 1);
		philo_print(philo, 0);
		return;
	}
	philo->ate = get_time();
	philo_print(philo, "is eating");
	philo->status = EAT;
	usleep(philo->arg->eat * 1000);
	pthread_mutex_unlock(&philo->right->mutex);
	pthread_mutex_unlock(&philo->left->mutex);
}

void	philo_sleep_think(t_philo *philo)
{
	philo->status = SLEEP;
	usleep(philo->arg->sleep * 1000);
	philo_print(philo, "is sleeping");
	philo->status = THINK;
	philo_print(philo, "is thinking");
}

void	*each_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)(data);
	if (philo->id % 2)
		usleep(philo->arg->eat * 1000);

	while (philo->status != DIED)
	{
		philo_eat(philo);
		philo_sleep_think(philo);
	}
	return (0);
}
