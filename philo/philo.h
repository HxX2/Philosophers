/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:13:44 by zlafou            #+#    #+#             */
/*   Updated: 2022/11/22 18:34:18 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_shared
{
	int				n_eat;
	clock_t			t_eat;
	clock_t			t_sleep;
	clock_t			t_stamp;
	clock_t			t_die;
	pthread_mutex_t	*m_msg;
	pthread_mutex_t	*m_eat;
	pthread_mutex_t	*m_span;

}		t_shared;

typedef struct s_philo
{
	int				id;
	int				n_eat;
	clock_t			t_span;
	pthread_t		thread_id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	t_shared		*sh;
}		t_philo;

typedef struct s_ph
{
	int				n_philos;
	t_philo			*philos;	
	pthread_mutex_t	*forks;
	pthread_mutex_t	*t_span;
	t_shared		*sh;
}		t_ph;

int		ft_atoi(const char *str);
void	*ft_calloc(size_t n);

int		arg_validator(char **av, int argn);
void	ft_usleep(clock_t ms);
void	throwerror(void);
clock_t	get_time(void);
void	msg(clock_t ts, int id, char *msg, pthread_mutex_t *mutex);
short	is_dead(clock_t time, t_ph *ph, int i);

int		init_data(t_ph *ph, int ac, char **av);
int		init_forks(t_ph *ph);
int		init_philos(t_ph *ph);

void	*philo_routine(void *targ);
void	take_forks(t_philo *philo);
int		create_threads(t_ph *ph);
short	supervisor(t_ph *ph);
void	eat(t_philo *philo);

#endif