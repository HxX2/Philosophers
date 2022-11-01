/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:31:20 by zlafou            #+#    #+#             */
/*   Updated: 2022/11/01 10:45:29 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *targ)
{
	t_philo	*philo;

	philo = (t_philo *)targ;
	while (1)
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->l_fork);
			msg(get_time() - philo->time_st, philo->id, "has taken a fork", philo->msg);
			pthread_mutex_lock(philo->r_fork);
			msg(get_time() - philo->time_st, philo->id, "has taken a fork", philo->msg);
		}
		else 
		{
			pthread_mutex_lock(philo->r_fork);
			msg(get_time() - philo->time_st, philo->id, "has taken a fork", philo->msg);
			pthread_mutex_lock(philo->l_fork);
			msg(get_time() - philo->time_st, philo->id, "has taken a fork", philo->msg);
		}
		msg(get_time() - philo->time_st, philo->id, "is eating", philo->msg);
		pthread_mutex_lock(philo->m_eat);
		if(philo->ac > 5)
			philo->n_eat--;
		pthread_mutex_unlock(philo->m_eat);
		pthread_mutex_lock(philo->t_span);
		philo->time_sp = get_time();
		pthread_mutex_unlock(philo->t_span);
		ft_usleep(philo->t_eat);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		msg(get_time() - philo->time_st, philo->id, "is sleeping", philo->msg);
		ft_usleep(philo->t_sleep);
		msg(get_time() - philo->time_st, philo->id, "is thinking", philo->msg);
	}
	return (NULL);
}

void	init_forks(t_ph *ph)
{
	int	i;

	ph->forks = ft_calloc(sizeof(pthread_mutex_t) * ph->n_philos);
	i = 0;
	while (i < ph->n_philos)
	{
		pthread_mutex_init(&ph->forks[i], NULL);
		i++;
	}
}

void	init_philos(t_ph *ph)
{
	int	i;

	i = 0;
	ph->philos = ft_calloc(sizeof(t_philo) * ph->n_philos);
	while (i < ph->n_philos)
	{
		ph->philos[i].id = i + 1;
		ph->philos[i].msg = ph->msg;
		ph->philos[i].m_eat = ph->m_eat;
		ph->philos[i].n_eat = &ph->n_eat;
		ph->philos[i].ac = ph->ac;
		ph->philos[i].t_span = ph->t_span;
		ph->philos[i].t_eat = ph->t_eat;
		ph->philos[i].t_sleep = ph->t_sleep;
		ph->philos[i].l_fork = &ph->forks[i];
		ph->philos[i].r_fork = &ph->forks[(i + 1) % ph->n_philos];
		i++;
	}
}

int	main(int ac, char **av)
{
	unsigned long	time_st;
	t_ph			ph;
	int				i;

	memset(&ph, 0, sizeof(t_ph));
	if (ac < 5)
		return (0);
	ph.n_philos = arg_validator(av, 1);
	ph.t_die = arg_validator(av, 2);
	ph.t_eat = arg_validator(av, 3);
	ph.t_sleep = arg_validator(av, 4);
	if (ac > 5)
	{
		ph.ac = ac;
		ph.n_eat = arg_validator(av, 5) * ph.n_philos;
	}
	ph.t_span = ft_calloc(sizeof(pthread_mutex_t));
	ph.msg = ft_calloc(sizeof(pthread_mutex_t));
	ph.m_eat = ft_calloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(ph.m_eat, NULL);
	pthread_mutex_init(ph.t_span, NULL);
	pthread_mutex_init(ph.msg, NULL);
	init_forks(&ph);
	init_philos(&ph);
	i = 0;
	time_st = get_time();
	while (i < ph.n_philos)
	{
		ph.philos[i].time_st = time_st;
		ph.philos[i].time_sp = time_st;
		pthread_create(&ph.philos[i].thread_id, NULL, philo_routine, (void *)&ph.philos[i]);
		i++;
	}
	i = 0;
	while (1)
	{
		pthread_mutex_lock(ph.philos[i % ph.n_philos].t_span);
		unsigned long time = get_time() - ph.philos[i % ph.n_philos].time_sp;
		pthread_mutex_lock(ph.m_eat);
		// printf("%d", ph.n_eat);
		if (ph.ac > 5 && ph.n_eat == 0)
			break ;		
		pthread_mutex_unlock(ph.m_eat);
		if (time > ph.t_die)
		{
			pthread_detach(ph.philos[i % ph.n_philos].thread_id);
			pthread_mutex_lock(ph.msg);
			printf("%lu %d died\n", time, ph.philos[i % ph.n_philos].id);
			break ;
		}
		pthread_mutex_unlock(ph.philos[i % ph.n_philos].t_span);
		i++;
	}
	return (0);
}

// philo number_of_philos time_to_die time_to_eat time_to_sleep