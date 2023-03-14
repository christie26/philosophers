/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:47:27 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/14 12:38:40 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

// in this function, they don't start eating. They just take forks
void	philo_init(t_philo *philo)
{
	int	i;
	int	num;

	i = philo->id;
	num = philo->arg->num;
	if (num % 2 == 0)
	{
		if (i % 2 == 0)
		{
			pthread_mutex_lock(philo->left->mutex);
			pthread_mutex_lock(philo->right->mutex);
			philo->left->fork = 1;
			philo->right->fork = 1;
		}
	}
	else
	{
		if (i % 2 == 0 && i != num - 1)
		{
			pthread_mutex_lock(philo->left->mutex);
			pthread_mutex_lock(philo->right->mutex);
			philo->left->fork = 1;
			philo->right->fork = 1;
		}
	}	
}

void	philo_eat(t_philo *philo)
{
	while (philo->status != EAT)
	{
		if (philo->left->fork == 0)
		{
			pthread_mutex_lock(philo->left->mutex);
			philo->left->fork = 1;
		}
		if (philo->right->fork == 0)
		{
			pthread_mutex_lock(philo->right->mutex);
			philo->right->fork = 1;
		}
		if (philo->left->fork && philo->right->fork)
		{
			if (time_stamp(philo->ate) > philo->arg->die)
			{
				philo->status = DIED;
				return;
			}
			philo->ate = get_time();
			printf("%d: %d start eat\n", time_stamp(philo->arg->start_time), philo->id + 1);
			philo->status = EAT;
		}
	}
	usleep(philo->arg->eat * 1000);	// eating
	philo->left->fork = 0;
	philo->right->fork = 0;
	pthread_mutex_unlock(philo->left->mutex);
	pthread_mutex_unlock(philo->right->mutex);

	philo->status = SLEEP;
	usleep(philo->arg->sleep * 1000);

	philo->status = THINK;

}

void	*each_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)(data);
	printf("I am %dth philosophers\n", philo->id + 1);

	philo_init(philo);
	while (philo->status != DIED)
	{
		philo_eat(philo);
	}
//	return ((void *)(long)(philo->id));
	return (0);
}
