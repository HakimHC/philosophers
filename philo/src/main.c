/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:52:52 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/17 10:50:57 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <sys/_types/_null.h>

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

pthread_mutex_t	*mk_forks(int n)
{
	int		i;
	pthread_mutex_t	*arr;

	arr = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < n)
		pthread_mutex_init((arr + i++), NULL);
	return (arr);
}

int	main(int argc, char **argv)
{
	int		params[5];
	long	start;

	if (err_handl(argc, argv, params) != EXIT_SUCCESS)
		return (EXIT_FAILURE);
	start = get_tm();
	while (42)
	{
		printf("ms: %li\n", get_tm() - start);
		mssleep(100);
	}
}
