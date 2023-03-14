/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:43:30 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/14 15:55:08 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_err_msg(int condition, char *error_message, char *file, int line)
{
	if (!condition)
		return ;
	write(2, file, ft_strlen(file));
	write(2, ":", 1);
	(void)(line);
//	ft_putnbr(line);
	write(2, ": error: ", 9);
	write(2, error_message, ft_strlen(error_message));
	write(2, "\n", 1);
	exit (1);
}

void	ft_err_sys(int condition, char *file, int line)
{
	if (!condition)
		return ;
	write(2, file, ft_strlen(file));
	write(2, ":", 1);
	(void)(line);
//	ft_putnbr(line);
	write(2, ": error", 9);
	exit (1);
}

struct timeval	get_time(void)
{
	struct timeval cur;

	gettimeofday(&cur, 0);
	return (cur);
}

int	time_stamp(struct timeval start)
{
	struct timeval cur;
	int	tv_sec;
	int	tv_usec;

	cur = get_time();
	tv_sec = (int)(cur.tv_sec - start.tv_sec);
	tv_usec = cur.tv_usec - start.tv_usec;
	tv_usec += tv_sec * 1000000;
	return (tv_usec/1000);
}

int	ft_atoi(const char *str)
{
	int			i;
	long long	sum;
	int			sign;

	i = 0;
	sum = 0;
	sign = 0;
	if (str[i] == '-')
	{
		sign = 1;
		i++;
	}
	while (('0' <= str[i]) && (str[i] <= '9'))
	{
		sum = (sum * 10) + (str[i] - '0');
		i++;
	}
	if (sign == 1)
		sum = -sum;
	return (sum);
}
