/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:13:44 by zlafou            #+#    #+#             */
/*   Updated: 2022/11/25 00:39:58 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <signal.h>
# include <string.h>

typedef struct s_shared
{
	int				n_eat;
	clock_t			t_eat;
	clock_t			t_sleep;
	clock_t			t_stamp;
	clock_t			t_die;
	sem_t			*m_eat;
	sem_t			*m_msg;

}		t_shared;

typedef struct s_philo
{
	int				id;
	int				n_eat;
	struct timeval	t_span;
	pthread_t		thread_id;
	sem_t			*forks;
	t_shared		*sh;
}		t_philo;

typedef struct s_ph
{
	int				n_philos;
	t_philo			*philos;	
	sem_t			*forks;
	t_shared		*sh;
	pid_t			*pids;
}		t_ph;

int		ft_atoi(const char *str);
void	*ft_calloc(size_t n);

int		arg_validator(char **av, int argn);
void	ft_usleep(clock_t ms);
void	throwerror(void);
clock_t	get_time(void);
void	msg(clock_t ts, int id, char *msg, sem_t *semaphore);
short	is_dead(clock_t time, t_ph *ph, int i);

void	init_data(t_ph *ph, int ac, char **av);
void	init_forks(t_ph *ph);
void	init_philos(t_ph *ph);

void	*philo_routine(void *targ);
void	take_forks(t_philo *philo);
void	create_proccess(t_ph *ph);
void	supervisor(t_ph *ph, int i);
void	eat(t_philo *philo);
void	ft_child(t_ph *ph, int i);
void	wait_on_proc(t_ph *ph);

#endif