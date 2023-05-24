/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:37:07 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/24 20:41:33 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	t_data	*res;

	*status = 0;
	res = malloc(sizeof(t_data));
	if (!res)
		return (set_status(status, ERR_MALLOC));
	res->params = malloc(5 * sizeof(int));
	if (!res->params)
		return (set_status(status, ERR_MALLOC));
	res->start = get_tm();
	if (pthread_mutex_init(&res->mtx_print, NULL))
		return (set_status(status, ERR_MTX));
	if (err_handl(argc, argv, res->params) != EXIT_SUCCESS)
		return (set_status(status, ERR_ARG));
	res->forks = mk_forks(res->params[NUM_PHIL], status);
	if (!res->forks)
		return (set_status(status, ERR_MALLOC));
	res->start = get_tm();
	return (res);
}
