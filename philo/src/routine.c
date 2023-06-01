/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 21:23:47 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/31 16:06:16 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

#include "philo.h"

int	take_fork(t_philo *p, int f)
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
		if (p->params[NUM_PHIL] == 1)
		{
			mssleep(p->params[TDIE]);
			return (1);
		}
		if (p->fork_r > p->fork_l)
			pthread_mutex_lock(p->fork_l);
		else
			pthread_mutex_lock(p->fork_r);
	}
	return (0);
}

int	check_d(t_philo *p)
{
	int	b;

	pthread_mutex_lock(p->glob->mtx_print);
	b = p->glob->end;
	pthread_mutex_unlock(p->glob->mtx_print);
	return (b);
}

int	sleep_n_think(t_philo **p)
{
	print_msg(p, SLEEPMSG);
	if (check_d(*p))
		return (0);
	mssleep((*p)->params[TSLEEP]);
	print_msg(p, THINKMSG);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = arg;
	if (p->number % 2 == 0)
		usleep(200);
	while (!p->glob->end)
	{
		take_fork(p, 1);
		print_msg(&p, FORKMSG);
		if (take_fork(p, 2))
			return (NULL);
		p->last_meal = get_curr_ms(p->glob->start);
		print_msg(&p, FORKMSG);
		print_msg(&p, EATMSG);
		p->meal_count++;
		if (check_d(p))
			return (NULL);
		mssleep(p->params[TEAT]);
		release_forks(p);
		if (!sleep_n_think(&p))
			return (NULL);
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
		i = -1;
		b = 0;
		while (++i < (data->params)[NUM_PHIL])
		{
			p = (data->p)[i];
			if (get_curr_ms(data->start) - p->last_meal > p->params[TDIE])
				return (print_death_msg(data, p->number), 1);
			if (p->params[OPT] != -1 && p->meal_count >= p->params[OPT])
				b++;
		}
		if (b == data->params[NUM_PHIL])
		{
			pthread_mutex_lock(data->mtx_print);
			data->end = 1;
			pthread_mutex_unlock(data->mtx_print);
			return (0);
		}
		usleep(20);
	}
}
