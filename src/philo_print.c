/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_print.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 18:29:13 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/14 18:47:41 by yoonsele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	find_digit(int n, int *flag, unsigned int *nb)
{
	int				cnt;
	unsigned int	tmp;

	if (n == 0)
	{
		*nb = 0;
		return (1);
	}
	cnt = 0;
	if (n < 0)
	{
		*nb = -n;
		cnt++;
		*flag = 1;
	}
	else
		*nb = n;
	tmp = *nb;
	while (tmp)
	{
		cnt++;
		tmp /= 10;
	}
	return (cnt);
}

char	*ft_itoa(int n)
{
	int				digit;
	unsigned int	nb;
	int				flag;
	char			*res;
	char			*tmp;

	digit = find_digit(n, &flag, &nb);
	res = (char *)malloc(sizeof(char) * (digit + 1));
	if (!res)
		return (0);
	tmp = res;
	if (flag)
		*tmp = '-';
	tmp += (digit - 1);
	if (nb == 0)
		res[0] = '0';
	while (nb != 0)
	{
		*tmp = nb % 10 + '0';
		tmp--;
		nb /= 10;
	}
	res[digit] = 0;
	return (res);
}

void	philo_print(t_philo *philo, int status)
{
	char	*time;
	char	*id;

	pthread_mutex_lock(&philo->arg->write);
	time = ft_itoa(time_stamp(philo->arg->start_time));
	id = ft_itoa(philo->id);
	write(1, time, ft_strlen(time));
	write(1, " ", 1);
	write(1, id, ft_strlen(id));
	write(1, " ", 1);
	if (status == 1)
		write(1, "has taken a fork\n", 17);
	else if (status == 2)
		write(1, "is eating\n", 10);
	else if (status == 3)
		write(1, "is sleeping\n", 12);
	else if (status == 4)
		write(1, "is thinking\n", 12);
	else
		write(1, "died\n", 5);
	pthread_mutex_unlock(&philo->arg->write);
	free(time);
	free(id);
}

/*
◦ timestamp_in_ms X has taken a fork
◦ timestamp_in_ms X is eating
◦ timestamp_in_ms X is sleeping
◦ timestamp_in_ms X is thinking
◦ timestamp_in_ms X died
*/
