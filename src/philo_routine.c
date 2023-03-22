/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_act.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 13:47:27 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/21 22:31:41 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->dead);
	if (*philo->arg->flag == 0)
	{
		*philo->arg->flag = 1;
		pthread_mutex_unlock(&philo->arg->dead);
		philo_print(philo, 0);
	}
	else
	{
		pthread_mutex_unlock(&philo->arg->dead);
	}
	philo->status = DIED;
	return (1);
}

int	philo_fork(t_philo *philo)
{
	if (take_lfork(philo))
	{
		philo_dead(philo);
		return (1);
	}
	if (ft_check_dead(philo))
		return (1);
	philo_print(philo, "has taken a fork");
	if (take_rfork(philo))
	{
		philo_dead(philo);
		return (1);
	}
	if (ft_check_dead(philo))
		return (1);
	philo_print(philo, "has taken a fork");
	return (0);
}

int	philo_eat(t_philo *philo)
{
	if (ft_check_dead(philo))
		return (1);
	philo->ate = ft_get_time();
	philo_print(philo, "is eating");
	ft_usleep(philo->arg->eat * 1000);
	pthread_mutex_lock(&philo->left->mutex);
	philo->left->status = 0;
	pthread_mutex_unlock(&philo->left->mutex);
	pthread_mutex_lock(&philo->right->mutex);
	philo->right->status = 0;
	pthread_mutex_unlock(&philo->right->mutex);
	philo->time += 1;
	if (philo->time == philo->arg->must && philo->arg->option)
	{
		return (1);
	}
	return (0);
}

int	philo_sleep_think(t_philo *philo)
{
	if (ft_check_dead(philo))
		return (1);
	philo_print(philo, "is sleeping");
	ft_usleep(philo->arg->sleep * 1000);
	if (ft_check_dead(philo))
		return (1);
	philo_print(philo, "is thinking");
	return (0);
}

void	*each_philo(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)(data);
	philo->ate = ft_get_time();
	if (philo->id % 2)
		usleep(500);
	while (philo->status != DIED)
	{
		if (philo_fork(philo))
			break ;
		if (philo_eat(philo))
			break ;
		if (philo_sleep_think(philo))
			break ;
		if (ft_check_dead(philo))
			break ;
	}
	return (0);
}
