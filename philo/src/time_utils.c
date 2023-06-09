/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 21:12:50 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/31 14:23:31 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/time.h>

#include "philo.h"

long	get_tm(void)
{
	t_time	tp;

	gettimeofday(&tp, NULL);
	return ((tp.tv_sec * 1000) + (tp.tv_usec / 1000));
}

void	mssleep(long ms)
{
	long	start;

	start = get_tm();
	while (get_tm() - start < ms)
		usleep(50);
}

long	get_curr_ms(long start)
{
	return (get_tm() - start);
}
