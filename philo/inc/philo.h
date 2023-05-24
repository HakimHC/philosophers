/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakahmed <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 23:52:26 by hakahmed          #+#    #+#             */
/*   Updated: 2023/05/24 21:26:40 by hakahmed         ###   ########.fr       */
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
# define FL "has taken the left fork"
# define FR "has taken the right fork"
# define EATMSG "is eating"
# define SLEEPMSG "is sleeping"
# define THINKMSG "is thinking"
# define DEATHMSG "died"

# define ERR_MALLOC 1
# define ERR_THREAD 2
# define ERR_ARG 3
# define ERR_MTX 4

typedef struct timeval	t_time;
typedef pthread_mutex_t	t_mtx;
typedef struct s_philo	t_philo;

typedef struct s_data
{
	long		start;
	int			*params;
	t_mtx		*forks;
	t_philo		**p;
	t_mtx		mtx_print;
}	t_data;

struct s_philo
{
	pthread_t	tid;
	int			number;
	int			*params;
	t_mtx		*fork_l;
	t_mtx		*fork_r;
	long		last_meal;
	int			meal_count;
	t_data		*glob;
};

/* time utilities */
void	mssleep(long ms);
long	get_tm(void);
long	get_curr_ms(long start);

/* parse utilities */
int		ft_isdigit(char c);
int		ft_isspace(char c);
int		ft_atoi(char *str);
int		ft_isinteger(char *element);

/* print utilities */
void	ft_putstr_fd(char *str, int fd);
void	print_msg(t_philo **p, char *msg);
void	print_death_msg(t_data *data, int n);

/* pthread utilities */
t_mtx	*mk_forks(int n, int *status);
t_philo	*mk_philo(int number, t_mtx *l, t_mtx *r, t_data *glob);
int		mk_threads(t_data *glob);

/* error handling */
int		err_handl(int argc, char **argv, int *params);
void	*set_status(int *status, int state);
int		print_error_msg(int status);

/* routine */
void	take_fork(t_philo *p, int f);
void	*routine(void *arg);
int		watchdog(t_data *data);

/* init */
int		populate_params(int *params, char **args);
t_data	*init_data(int argc, char **argv, int *status);

void	*routine(void *arg);

#endif
