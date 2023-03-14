/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:47:27 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/14 17:08:16 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(philo->left->mutex);
	printf("%d %d has taken a left fork\n", time_stamp(philo->arg->start_time), philo->id);
	pthread_mutex_lock(philo->right->mutex);
	printf("%d %d has taken a right fork\n", time_stamp(philo->arg->start_time), philo->id);
	if (time_stamp(philo->ate) > philo->arg->die)
	{
		philo->status = DIED;
		return;
	}
	philo->ate = get_time();
	printf("%d %d is eating\n", time_stamp(philo->arg->start_time), philo->id);
	philo->status = EAT;
	usleep(philo->arg->eat * 1000);	// eating
	pthread_mutex_unlock(philo->right->mutex);
	pthread_mutex_unlock(philo->left->mutex);

	philo->status = SLEEP;
	usleep(philo->arg->sleep * 1000);

	philo->status = THINK;

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
	printf("%d %d died\n", time_stamp(philo->arg->start_time), philo->id);
	return (0);
}
