/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 11:43:48 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/18 20:43:37 by yoonsele         ###   ########.fr       */
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

int	ft_err_msg(int condition, char *error_message)
{
	if (!condition)
		return (0);
	printf("Error: %s\n", error_message);
	return (1);
}

int	ft_atoi(char *str)
{
	int			i;
	long long	sum;

	i = 0;
	sum = 0;
	while (('0' <= str[i]) && (str[i] <= '9'))
	{
		sum = (sum * 10) + (str[i] - '0');
		i++;
	}
	if (i != ft_strlen(str))
		return (0);
	return (sum);
}
