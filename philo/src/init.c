/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:37:07 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/31 14:27:37 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>

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

t_data	*init_data(int argc, char **argv, int *status)
{
	t_data	*data;

	*status = 0;
	data = malloc(sizeof(t_data));
	if (!data)
		return (set_status(status, ERR_MALLOC));
	data->params = malloc(5 * sizeof(int));
	if (!data->params)
		return (free(data), set_status(status, ERR_MALLOC));
	data->start = get_tm();
	if (err_handl(argc, argv, data->params) != EXIT_SUCCESS)
		return (free(data->params), free(data), set_status(status, ERR_ARG));
	data->mtx_print = malloc(sizeof(t_mtx));
	if (!data->mtx_print)
		return (set_status(status , ERR_MALLOC));
	if (pthread_mutex_init(data->mtx_print, NULL))
		return (free(data->params), free(data), set_status(status, ERR_MTX));
	data->forks = mk_forks(data->params[NUM_PHIL], status);
	if (!data->forks)
	{
		pthread_mutex_destroy(data->mtx_print);
		return (free(data), free(data->params), set_status(status, ERR_MALLOC));
	}
	data->start = get_tm();
	data->end = 0;
	return (data);
}
