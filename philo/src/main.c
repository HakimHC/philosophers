/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:52:52 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/24 20:34:18 by hakahmed         ###   ########.fr       */
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
		if (p->fork_r > p->fork_l)
			pthread_mutex_lock(p->fork_r);
		else
			pthread_mutex_lock(p->fork_l);
		print_msg(&p, FR);
		if (p->fork_r > p->fork_l)
			pthread_mutex_lock(p->fork_l);
		else
			pthread_mutex_lock(p->fork_r);
		p->last_meal = get_curr_ms(p->glob->start);
		print_msg(&p, FL);
		print_msg(&p, EATMSG);
		p->meal_count++;
		mssleep(p->params[TEAT]);
		pthread_mutex_unlock(p->fork_r);
		pthread_mutex_unlock(p->fork_l);
		print_msg(&p, SLEEPMSG);
		mssleep(p->params[TSLEEP]);
		print_msg(&p, THINKMSG);
	}
	return (NULL);
}

int	watchdog(t_data *data)
{
	int	i;
	int	b;
	t_philo	*p;

	while (1)
	{
		i = 0;
		b = 0;
		while (i < (data->params)[NUM_PHIL])
		{
			p = (data->p)[i];
			if (get_curr_ms(data->start) - p->last_meal > p->params[TDIE])
			{
				pthread_mutex_lock(&(data->mtx_print));
				printf("%li ms: %d died\n", get_curr_ms(data->start), p->number);
				pthread_mutex_unlock(&(data->mtx_print));
				return 1;
			}
			if (p->params[OPT] != -1 && p->meal_count >= p->params[OPT])
				b++;
			i++;
		}
		if (b == data->params[NUM_PHIL])
			return 0;
	}
}

int	main(int argc, char **argv)
{
	t_data		*res;
	int		status;
	
	res = init_data(argc, argv, &status);
	if (status)
		return (print_error_msg(status));
	mk_threads(res);
	if (!watchdog(res))
		printf("Everyone has eaten %d times, ending simulation...\n", res->params[OPT]);
}
