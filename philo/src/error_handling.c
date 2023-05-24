/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <hakahmed@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:19:05 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/24 15:00:07 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	err_handl(int argc, char **argv, int *params)
{
	if (argc > 6 || argc < 5)
		return (1);
	if (populate_params(params, argv) == 1)
		return (1);
	return (0);
}

void	*set_status(int *status, int state)
{
	*status = state;
	return (NULL);
}

int	print_error_msg(int status)
{
	if (status == ERR_ARG)
	{
		ft_putstr_fd("fatal: invalid arguments\n", 2);
		ft_putstr_fd("usage: ./philo num_philo time_to_die ", 2);
		ft_putstr_fd("time_to_eat time_to_sleep [num_times_to_eat]", 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("arguments must be positive integers\n", 2);
	}
	if (status == ERR_MALLOC)
		ft_putstr_fd("fatal: malloc: can't allocate memory\n", 2);
	if (status == ERR_MTX)
		ft_putstr_fd("fatal: mutex_init: can't initialize mutex\n", 2);
	if (status == ERR_THREAD)
		ft_putstr_fd("fatal: pthread_create: can't create thread", 2);
	return (1);
}
