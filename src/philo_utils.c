/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:29:13 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/21 22:30:25 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	take_lfork(t_philo *philo)
{
	while (1)
	{
		if (time_stamp(philo->ate) > philo->arg->die)
			return (1);
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
			usleep(300);
		}
	}
	return (0);
}

int	take_rfork(t_philo *philo)
{
	while (1)
	{
		if (time_stamp(philo->ate) > philo->arg->die)
			return (1);
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
			usleep(300);
		}
	}
	return (0);
}

void	philo_print(t_philo *philo, char *message)
{
	if (message == 0)
	{
		pthread_mutex_lock(&philo->arg->write);
		printf("%d %d %s\n", time_stamp(philo->arg->start_time), \
				philo->id, "died");
		pthread_mutex_unlock(&philo->arg->write);
		return ;
	}
	pthread_mutex_lock(&philo->arg->write);
	if (!ft_check_dead(philo))
		printf("%d %d %s\n", time_stamp(philo->arg->start_time), \
				philo->id, message);
	pthread_mutex_unlock(&philo->arg->write);
}

int	ft_check_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->arg->dead);
	if (*philo->arg->flag)
	{
		pthread_mutex_unlock(&philo->arg->dead);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->arg->dead);
		return (0);
	}
}

void	philo_wait(t_philo *philo)
{
	int		waiting;

	pthread_mutex_lock(&philo->arg->ready);
	*philo->arg->ready_num += 1;
	if (*philo->arg->ready_num == philo->arg->num)
		philo->arg->start_time = ft_get_time();
	pthread_mutex_unlock(&philo->arg->ready);
	waiting = 1;
	while (waiting)
	{
		pthread_mutex_lock(&philo->arg->ready);
		waiting = (*philo->arg->ready_num != philo->arg->num);
		pthread_mutex_unlock(&philo->arg->ready);
		usleep(100);
	}
}
