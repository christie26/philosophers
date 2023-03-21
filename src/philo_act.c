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

int	take_lfork(t_philo *philo)
{
	while (1)
	{
		if (time_stamp(philo->ate) > philo->arg->die)
		{
			philo->status = DIED;
			return (1);
		}
		pthread_mutex_lock(&philo->left->mutex);
		if (philo->left->status == 0)
		{
			philo->left->status = 1;
			pthread_mutex_unlock(&philo->left->mutex);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&philo->left->mutex);
			ft_usleep(100);
		}
	}
	return (0);
}

int	take_rfork(t_philo *philo)
{
	while (1)
	{
		if (time_stamp(philo->ate) > philo->arg->die)
		{
			philo->status = DIED;
			return (1);
		}
		pthread_mutex_lock(&philo->right->mutex);
		if (philo->right->status == 0)
		{
			philo->right->status = 1;
			pthread_mutex_unlock(&philo->right->mutex);
			break ;
		}
		else
		{
			pthread_mutex_unlock(&philo->right->mutex);
			ft_usleep(100);
		}
	}
	return (0);
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
	philo->ate = get_time();
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
		return (1);
	return (0);
}

void	*each_philo(void *data)
{
	t_philo	*philo;
	int		waiting;

	philo = (t_philo *)(data);
	pthread_mutex_lock(philo->arg->ready);
	*philo->arg->ready_num += 1;
	pthread_mutex_unlock(philo->arg->ready);
	waiting = 1;
	while (waiting)
	{
		pthread_mutex_lock(philo->arg->ready);
		waiting = (*philo->arg->ready_num != philo->arg->num);
		pthread_mutex_unlock(philo->arg->ready);
		usleep(100);
	}
	philo->ate = get_time();
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
