/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:52:26 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/17 14:26:28 by hakim            ###   ########.fr       */
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
typedef pthread_mutex_t	t_mtx;

typedef struct s_philo
{
	pthread_t	tid;
	int				number;
	int				*params;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	long			last_meal;
}					t_philo;

typedef struct s_shared
{
	int	*params;
	long	start;
}	t_shared;

/* utilities */
void	mssleep(long ms);
long	get_tm(void);
int		ft_isdigit(char c);
int		ft_isspace(char c);
int		ft_atoi(char *str);
int		ft_isinteger(char *element);
void	ft_putstr_fd(char *str, int fd);

#endif
