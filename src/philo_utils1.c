/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:43:30 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/18 16:01:55 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

struct timeval	get_time(void)
{
	struct timeval	cur;

	gettimeofday(&cur, 0);
	return (cur);
}

int	time_stamp(struct timeval start)
{
	struct timeval	cur;
	int				tv_sec;
	int				tv_usec;

	cur = get_time();
	tv_sec = (int)(cur.tv_sec - start.tv_sec);
	tv_usec = cur.tv_usec - start.tv_usec;
	tv_usec += tv_sec * 1000000;
	return (tv_usec / 1000);
}

void	ft_usleep(int time)
{
	struct timeval	start;

	start = get_time();
	while (time_stamp(start) < time / 1000)
	{
		usleep(100);
	}
}
