/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:52:52 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/24 11:41:41 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "philo.h"

int	populate_params(int *params, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		params[i - 1] = ft_atoi(args[i]);
		if (params[i - 1] < 0 || !ft_isinteger(args[i]))
			return (EXIT_FAILURE);
		i++;
	}
	if (i == 5)
		params[i - 1] = -1;
	return (EXIT_SUCCESS);
}

int	err_handl(int argc, char **argv, int *params)
{
	if (argc > 6 || argc < 5)
	{
		ft_putstr_fd("fatal: invalid argument count\n", 2);
		return (EXIT_FAILURE);
	}
	if (populate_params(params, argv) == EXIT_FAILURE)
	{
		ft_putstr_fd("fatal: arguments must be positive integers\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

t_mtx	*mk_forks(int n)
{
	int		i;
	pthread_mutex_t	*arr;

	arr = (pthread_mutex_t *) malloc(n * sizeof(pthread_mutex_t));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < n)
		pthread_mutex_init((arr + i++), NULL);
	return (arr);
}

t_philo	*mk_philo(int number, pthread_mutex_t *l, pthread_mutex_t *r, t_shared glob)
{
	t_philo	*p;

	p = malloc(sizeof(t_philo));
	if (!p)
		return ((t_philo *)NULL);
	p->number = number;
	p->params = glob.params;
	p->fork_l = l;
	p->fork_r = r;
	p->glob = glob;
	return (p);
}

void	print_msg(t_philo *p, char *msg)
{
	printf("%li ms: %d ", get_curr_ms(p->glob.start), p->number);
	printf("%s\n", msg);
}

void	*routine(void *arg)
{
	t_philo	*p;

	p = arg;
	while (1)
	{
		pthread_mutex_lock(p->fork_r);
		print_msg(p, FORKMSG);
		pthread_mutex_lock(p->fork_l);
		print_msg(p, FORKMSG);
		print_msg(p, EATMSG);
		p->last_meal = get_tm() - p->glob.start;
		mssleep(p->params[TEAT]);
		pthread_mutex_unlock(p->fork_r);
		pthread_mutex_unlock(p->fork_l);
		print_msg(p, SLEEPMSG);
		mssleep(p->params[TSLEEP]);
		print_msg(p, THINKMSG);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_shared	resc;
	t_philo		*p1;
	t_philo		*p2;
	t_mtx		*forks;
	
	resc.start = get_tm();
	resc.params = malloc(5 * sizeof(int));
	if (!resc.params)
		ft_putstr_fd("malloc: cant allocate mem\n", 2);
	if (err_handl(argc, argv, resc.params) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	forks = mk_forks(2);
	p1 = mk_philo(1, forks, forks + 1, resc);
	p2 = mk_philo(2, forks, forks + 1, resc);
	pthread_create(&(p1->tid), NULL, routine, p1);
	pthread_create(&(p2->tid), NULL, routine, p2);
	pthread_join(p1->tid, NULL);
	pthread_join(p2->tid, NULL);
	free(resc.params);
}
