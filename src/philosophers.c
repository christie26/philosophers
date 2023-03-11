/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:47:27 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/10 21:05:06 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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
			printf("%d start eating\n", philo->id);
			
			philo->status = EAT;
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
			printf("%d start eating\n", philo->id);
			philo->status = EAT;
		}
	}	
}

void	philo_eat(t_philo *philo)
{

	while (philo->status != EAT)
	{
		sleep(3);
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
			printf("%d start eating\n", philo->id);
			philo->status = EAT;
		}
	}

	usleep(philo->arg->eat);	// eating
	printf("%d finish eating\n", philo->id);
	philo->left->fork = 0;	
	philo->right->fork = 0;	
	pthread_mutex_unlock(philo->left->mutex);
	pthread_mutex_unlock(philo->right->mutex);

	philo->status = SLEEP;
	printf("%d start sleeping\n", philo->id);
	usleep(philo->arg->sleep);
	printf("%d finish sleeping\n", philo->id);

	philo->status = THINK;

}

void	*each_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)(data);
	printf("I am %dth philosophers\n", philo->id);

	philo_init(philo);
	while (philo->status != DIED)
	{
		philo_eat(philo);	
	}	
	return ((void *)(long)(philo->id));
}
