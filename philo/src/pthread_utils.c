/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:34:56 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/24 20:49:54 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>

#include "philo.h"

t_mtx	*mk_forks(int n, int *status)
{
	int		i;
	t_mtx	*arr;

	arr = (pthread_mutex_t *) malloc(n * sizeof(pthread_mutex_t));
	if (!arr)
		return (set_status(status, ERR_MALLOC));
	i = 0;
	while (i < n)
	{
		if (pthread_mutex_init((arr + i++), NULL))
			return (set_status(status, ERR_MTX));
	}
	return (arr);
}

t_philo	*mk_philo(int number, t_mtx *l, t_mtx *r, t_data *glob)
{
	t_philo	*p;

	p = malloc(sizeof(t_philo));
	if (!p)
		return ((t_philo *) NULL);
	p->number = number;
	p->params = glob->params;
	p->fork_l = l;
	p->fork_r = r;
	p->glob = glob;
	p->meal_count = 0;
	return (p);
}

int	mk_threads(t_data *glob)
{
	t_philo	**philos;
	int		i;
	int		n;

	n = glob->params[NUM_PHIL];
	philos = malloc(n * sizeof(t_philo *));
	if (!philos)
		return (ERR_MALLOC);
	i = 0;
	while (i < n)
	{
		philos[i] = mk_philo(i + 1, &glob->forks[(i + n - 1) % n],
				&glob->forks[i], glob);
		if (!philos[i])
			return (ERR_MALLOC);
		if (pthread_create(&(philos[i]->tid), NULL, routine, philos[i]))
			return (ERR_THREAD);
		i++;
	}
	glob->p = philos;
	return (0);
}
