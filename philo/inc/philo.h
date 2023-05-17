/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:52:26 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/17 10:43:04 by hakahmed         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>

# define NUM_PHIL 0
# define TDIE 1
# define TEAT 2
# define TSLEEP 3
# define OPT 4

typedef struct timeval	t_time;

typedef struct s_philo
{
	int				number;
	int				params[5];
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	long			last_meal;
}					t_philo;

/* utilities */
void	mssleep(long ms);
long	get_tm(void);
int		ft_isdigit(char c);
int		ft_isspace(char c);
int		ft_atoi(char *str);
int		ft_isinteger(char *element);
void	ft_putstr_fd(char *str, int fd);

#endif
