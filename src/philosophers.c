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
			printf("init %d start eating\n", philo->id);
			philo->ate = get_time()/1000;
		//	printf("%d %d\n", philo->id, philo->ate);	
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
			printf("init %d start eating\n", philo->id);
			philo->ate = get_time()/1000;	
		//	printf("%d %d\n", philo->id, philo->ate);	
			philo->status = EAT;
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
			if (get_time()/1000 - philo->ate > philo->arg->die)
			{
				philo->status = DIED;
		//		printf("%d died \n", philo->id);
				exit (1);
			}
			philo->ate = get_time()/1000;
			printf("%d start eat %d\n", philo->id, philo->ate);	
			philo->status = EAT;
		}
	}
	usleep(philo->arg->eat * 1000);	// eating
//	printf("%d finish eat %d\n", philo->id, get_time()/1000);
	philo->left->fork = 0;
	philo->right->fork = 0;
	pthread_mutex_unlock(philo->left->mutex);
	pthread_mutex_unlock(philo->right->mutex);

	philo->status = SLEEP;
//	printf("%d start sleep %d\n", philo->id, get_time()/1000);
	usleep(philo->arg->sleep * 1000);
//	printf("%d finish sleep %d\n", philo->id, get_time()/1000);

	philo->status = THINK;

}

void	*each_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)(data);
	printf("I am %dth philosophers\n", philo->id);

	philo_init(philo);
	printf("%d %d\n", philo->id, get_time()/1000);
	while (philo->status != DIED)
	{
		philo_eat(philo);	
	}	
	return ((void *)(long)(philo->id));
}
