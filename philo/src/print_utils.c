/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:13:53 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/31 14:47:13 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "philo.h"

void	print_msg(t_philo **p, char *msg)
{
	pthread_mutex_lock(((*p)->glob->mtx_print));
	if (!(*p)->glob->end)
	{
		printf("%li\t%d ", get_curr_ms((*p)->glob->start), (*p)->number);
		printf("%s\n", msg);
	}
	pthread_mutex_unlock(((*p)->glob->mtx_print));
}

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}

void	print_death_msg(t_data *data, int n)
{
	pthread_mutex_lock(data->mtx_print);
	data->end = 1;
	printf("%li ms: %d died\n", get_curr_ms(data->start), n);
	pthread_mutex_unlock(data->mtx_print);
}
