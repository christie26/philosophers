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

void *each_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)(data);
	printf("I am %dth philosophers\n", philo->id);

	pthread_mutex_lock(philo->left->mutex);
	printf("Philosopher %d is using left fork\n", philo->id + 1);
	pthread_mutex_unlock(philo->left->mutex);

	pthread_mutex_lock(philo->right->mutex);
	printf("Philosopher %d is using right fork\n", philo->id + 1);
	pthread_mutex_unlock(philo->right->mutex);
	return ((void *)(long)(philo->id));
}
