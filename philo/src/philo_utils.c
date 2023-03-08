/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoonsele <yoonsele@student.42.kr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 17:43:30 by yoonsele          #+#    #+#             */
/*   Updated: 2023/03/07 17:44:11 by yoonsele         ###   ########.fr       */
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

int	what_time(t_argv arg)
{
	struct timeval cur;
	gettimeofday(&cur, 0);

	printf("rn it's %d\n", cur.tv_usec - arg.start_time);
	return (cur.tv_usec - arg.start_time);
}
