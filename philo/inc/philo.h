/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:52:26 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/24 11:40:01 by hakahmed         ###   ########.fr       */
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
# define FORKMSG "has taken a fork"
# define EATMSG "is eating"
# define SLEEPMSG "is sleeping"
# define THINKMSG "is thinking"

typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mtx;


typedef struct s_shared
{
	int	*params;
	long	start;
}	t_shared;

typedef struct s_philo
{
	pthread_t	tid;
	int				number;
	int				*params;
	pthread_mutex_t	*fork_l;
	pthread_mutex_t	*fork_r;
	long			last_meal;
	t_shared	glob;
}					t_philo;

/* utilities */
void	mssleep(long ms);
long	get_tm(void);
int		ft_isdigit(char c);
int		ft_isspace(char c);
int		ft_atoi(char *str);
int		ft_isinteger(char *element);
void	ft_putstr_fd(char *str, int fd);
long	get_curr_ms(long start);

#endif
