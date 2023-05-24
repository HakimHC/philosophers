/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:13:53 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/24 14:31:47 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

#include "philo.h"

void	print_msg(t_philo **p, char *msg)
{
	pthread_mutex_lock(&(*p)->glob->mtx_print);
	printf("%li ms: %d ", get_curr_ms((*p)->glob->start), (*p)->number);
	printf("%s\n", msg);
	pthread_mutex_unlock(&(*p)->glob->mtx_print);
}

void	ft_putstr_fd(char *str, int fd)
{
	while (*str)
		write(fd, str++, 1);
}
