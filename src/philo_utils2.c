/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:43:48 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/17 11:45:17 by yoonsele         ###   ########.fr       */
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
