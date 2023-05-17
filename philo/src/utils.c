/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:32:14 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/16 21:22:14 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <limits.h>

#include "philo.h"

int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

int	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

int	ft_atoi(char *str)
{
	int	i;
	int	res;
	int	sign;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}
	while (ft_isdigit(str[i]))
	{
		res = res * 10;
		res += str[i] - 48;
		i++;
	}
	return (res * sign);
}

int	ft_isinteger(char *element)
{
	long	n;
	long	sign;
	int		i;

	n = 0;
	sign = 1;
	i = -1;
	while (ft_isspace(element[++i]))
		;
	if (element[i] == '-' || element[i] == '+')
	{
		if (element[i] == '-')
			sign = -sign;
		i++;
	}
	while (ft_isdigit(element[i]))
	{
		n = (n * 10) + (element[i] - 48);
		if (n * sign > INT_MAX || n * sign < INT_MIN)
			return (0);
		i++;
	}
	while (ft_isspace(element[i++]))
		;
	return (!(element[i - 1]));
}

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}
