/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:13:44 by zlafou            #+#    #+#             */
/*   Updated: 2022/11/01 10:41:32 by zlafou           ###   ########.fr       */
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

typedef struct s_philo
{
	int				id;
	int				ac;
	int				*n_eat;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	unsigned long	time_st;
	unsigned long	time_sp;
	pthread_t		thread_id;
	pthread_mutex_t	*t_span;
	pthread_mutex_t	*msg;
	pthread_mutex_t	*m_eat;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
}		t_philo;

typedef struct s_ph
{
	int				n_philos;
	int				ac;
	int				n_eat;
	unsigned long	t_eat;
	unsigned long	t_sleep;
	unsigned long	t_die;
	t_philo			*philos;	
	pthread_mutex_t	*m_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*msg;
	pthread_mutex_t	*t_span;
}		t_ph;

int		ft_atoi(const char *str);
void	*ft_calloc(size_t n);

int				arg_validator(char **av, int argn);
void			ft_usleep(unsigned long ms);
void			throwerror(void);
unsigned long	get_time(void);
void	msg(unsigned long ts, int id, char *msg, pthread_mutex_t *mutex);


#endif