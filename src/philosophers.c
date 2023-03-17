/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:47:27 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/17 11:39:32 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->left->mutex);
	pthread_mutex_lock(&philo->right->mutex);
	philo_print(philo, 1);
	if (time_stamp(philo->ate) > philo->arg->die)
	{
		philo->status = DIED;
		return;
	}
	philo->ate = get_time();
	philo_print(philo, 2);
	philo->status = EAT;
	usleep(philo->arg->eat * 1000);
	pthread_mutex_unlock(&philo->right->mutex);
	pthread_mutex_unlock(&philo->left->mutex);
	philo->status = SLEEP;
	usleep(philo->arg->sleep * 1000);
	philo_print(philo, 3);
	philo->status = THINK;
	philo_print(philo, 4);
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
	}
	philo_print(philo, 5);
	return (0);
}
