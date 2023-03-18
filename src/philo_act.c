/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:47:27 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/18 19:23:57 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// 0: get fork
// 1: died
int	take_lfork(t_philo *philo)
{
	int	take;

	take = 0;
	while (!take)
	{
		if (time_stamp(philo->ate) > philo->arg->die)
		{
			philo->status = DIED;
			return (1);
		}
		pthread_mutex_lock(&philo->left->mutex);
		if (philo->left->status == 0)
		{
			philo->left->status = philo->id;
			pthread_mutex_unlock(&philo->left->mutex);
			take = 1;
		}
		pthread_mutex_unlock(&philo->left->mutex);
		usleep(1000);
	}
	return (0);
}

int	take_rfork(t_philo *philo)
{
	int	take;

	take = 0;
	while (!take)
	{
		if (time_stamp(philo->ate) > philo->arg->die)
		{
			philo->status = DIED;
			return (1);
		}
		pthread_mutex_lock(&philo->right->mutex);
		if (philo->right->status == 0)
		{
			philo->right->status = philo->id;
			pthread_mutex_unlock(&philo->right->mutex);
			take = 1;
		}
		pthread_mutex_unlock(&philo->right->mutex);
		usleep(1000);
	}
	return (0);
}

void	philo_fork(t_philo *philo)
{
	if (take_lfork(philo))
	{
		philo_dead(philo, 1);
		return ;
	}
	if (philo_dead(philo, 0))
		return ;
	philo_print(philo, "has taken a fork");
	if (take_rfork(philo))
	{
		philo_dead(philo, 1);
		return ;
	}
	if (philo_dead(philo, 0))
		return ;
	philo_print(philo, "has taken a fork");
}

void	philo_eat(t_philo *philo)
{
	philo->ate = get_time();
	if (philo_dead(philo, 0))
		return ;
	philo_print(philo, "is eating");
	usleep(philo->arg->eat * 1000);
	pthread_mutex_lock(&philo->right->mutex);
	philo->right->status = 0;
	pthread_mutex_unlock(&philo->right->mutex);
	pthread_mutex_lock(&philo->left->mutex);
	philo->left->status = 0;
	pthread_mutex_unlock(&philo->left->mutex);
}

void	*each_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)(data);
	if (philo->id % 2)
		usleep(philo->arg->eat * 1000);
	while (philo->status != DIED)
	{
		if (philo_dead(philo, 0))
			break ;
		philo_fork(philo);
		philo_eat(philo);
		philo_sleep_think(philo);
	}
	return (0);
}
