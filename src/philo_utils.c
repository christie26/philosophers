/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:43:30 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/10 21:01:02 by yoonsele         ###   ########.fr       */
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

int	get_time(void)
{
	struct timeval cur;

	gettimeofday(&cur, 0);
	printf("tv_sec: %ld\n", cur.tv_sec);
	printf("tv_usec: %d\n", cur.tv_usec);
	return (cur.tv_usec);
}

int	what_time(t_argv arg)
{
	struct timeval cur;

	gettimeofday(&cur, 0);
	printf("rn it's %d\n", cur.tv_usec - arg.start_time);
	return (cur.tv_usec - arg.start_time);
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
