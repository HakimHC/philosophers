/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:52:52 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/24 14:59:27 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include "philo.h"

void	*routine(void *arg)
{
	t_philo	*p;

	p = arg;
	if (p->number % 2 == 0)
		usleep(200);
	while (1)
	{
		pthread_mutex_lock(p->fork_r);
		print_msg(&p, FR);
		pthread_mutex_lock(p->fork_l);
		print_msg(&p, FL);
		print_msg(&p, EATMSG);
		p->last_meal = get_tm() - p->glob->start;
		mssleep(p->params[TEAT]);
		pthread_mutex_unlock(p->fork_r);
		pthread_mutex_unlock(p->fork_l);
		print_msg(&p, SLEEPMSG);
		mssleep(p->params[TSLEEP]);
		print_msg(&p, THINKMSG);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data		*res;
	int		status;
	
	res = init_data(argc, argv, &status);
	if (status)
		return (print_error_msg(status));
	mk_threads(res);
}
