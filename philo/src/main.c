/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:52:52 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/24 22:10:24 by hakahmed         ###   ########.fr       */
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
		pthread_detach(p->tid);
		free(p);
		i++;
	}
	free(philos);
}

void	destroyer(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->params[NUM_PHIL])
		pthread_mutex_destroy((data->forks) + i++);
	free(data->params);
	free(data);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	int		status;

	data = init_data(argc, argv, &status);
	if (status)
		return (print_error_msg(status));
	status = mk_threads(data);
	if (status)
		return (print_error_msg(status));
	if (watchdog(data) == EXIT_SUCCESS)
	{
		kill_them_all(data);
		pthread_mutex_lock(&(data->mtx_print));
		printf("Everyone has eaten %d times, ending simulation...\n",
			data->params[OPT]);
		pthread_mutex_unlock(&(data->mtx_print));
	}
	/* destroyer(data); */
}
