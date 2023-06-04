/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:52:52 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/31 15:17:32 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "philo.h"

void	kill_them_all(t_data *data)
{
	t_philo	**philos;
	t_philo	*p;
	int		i;

	i = 0;
	philos = data->p;
	while (i < data->params[NUM_PHIL])
	{
		p = (data->p)[i];
		pthread_join(data->p[i]->tid, NULL);
		free(p);
		i++;
	}
	free(philos);
	pthread_mutex_destroy(data->mtx_print);
	free(data->mtx_print);
}

void	destroyer(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->params[NUM_PHIL])
		pthread_mutex_destroy((data->forks) + i++);
	free(data->forks);
	free(data->params);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		status;

	status = 0;
	data = init_data(argc, argv, &status);
	if (status)
		return (print_error_msg(status));
	status = mk_threads(data);
	if (status)
		return (print_error_msg(status));
	if (watchdog(data) == EXIT_SUCCESS)
	{
		pthread_mutex_lock(data->mtx_print);
		printf("Everyone has eaten %d times, ending simulation...\n",
			data->params[OPT]);
		pthread_mutex_unlock(data->mtx_print);
	}
	kill_them_all(data);
	destroyer(data);
}
