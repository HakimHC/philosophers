/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 21:23:47 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/24 21:26:29 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "philo.h"

void	take_fork(t_philo *p, int f)
{
	if (f == 1)
	{
		if (p->fork_r > p->fork_l)
			pthread_mutex_lock(p->fork_r);
		else
			pthread_mutex_lock(p->fork_l);
	}
	else
	{
		if (p->fork_r > p->fork_l)
			pthread_mutex_lock(p->fork_l);
		else
			pthread_mutex_lock(p->fork_r);
	}
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = arg;
	if (p->number % 2 == 0)
		usleep(200);
	while (1)
	{
		take_fork(p, 1);
		print_msg(&p, FORKMSG);
		take_fork(p, 2);
		p->last_meal = get_curr_ms(p->glob->start);
		print_msg(&p, FORKMSG);
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
	int		i;
	int		b;
	t_philo	*p;

	while (1)
	{
		i = 0;
		b = 0;
		while (i < (data->params)[NUM_PHIL])
		{
			p = (data->p)[i];
			if (get_curr_ms(data->start) - p->last_meal > p->params[TDIE])
				return (print_death_msg(data, p->number), 1);
			if (p->params[OPT] != -1 && p->meal_count >= p->params[OPT])
				b++;
			i++;
		}
		if (b == data->params[NUM_PHIL])
			return (0);
	}
}