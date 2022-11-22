/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 23:00:49 by zlafou            #+#    #+#             */
/*   Updated: 2022/11/22 19:28:07 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	pthread_mutex_lock(philo->r_fork);
	msg(get_time() - philo->sh->t_stamp, philo->id, "has taken a r fork",
		philo->sh->m_msg);
	msg(get_time() - philo->sh->t_stamp, philo->id, "has taken a l fork",
		philo->sh->m_msg);
}

void	eat(t_philo *philo)
{
	msg(get_time() - philo->sh->t_stamp, philo->id, "is eating",
		philo->sh->m_msg);
	pthread_mutex_lock(philo->sh->m_eat);
	if (philo->n_eat)
		philo->n_eat--;
	pthread_mutex_unlock(philo->sh->m_eat);
}

void	*philo_routine(void *targ)
{
	t_philo	*philo;

	philo = (t_philo *)targ;
	while (1)
	{
		take_forks(philo);
		eat(philo);
		pthread_mutex_lock(philo->sh->m_span);
		philo->t_span = get_time();
		pthread_mutex_unlock(philo->sh->m_span);
		ft_usleep(philo->sh->t_eat);
		pthread_mutex_unlock(philo->r_fork);
		pthread_mutex_unlock(philo->l_fork);
		msg(get_time() - philo->sh->t_stamp, philo->id, "is sleeping",
			philo->sh->m_msg);
		ft_usleep(philo->sh->t_sleep);
		msg(get_time() - philo->sh->t_stamp, philo->id, "is thinking",
			philo->sh->m_msg);
	}
	return (NULL);
}

void	msg(unsigned long ts, int id, char *msg, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%lu %d %s\n", ts, id, msg);
	pthread_mutex_unlock(mutex);
}

short	supervisor(t_ph *ph)
{
	int		i;
	clock_t	time;
	int		ne;

	while (1)
	{
		i = 0;
		ne = 0;
		while (i < ph->n_philos)
		{
			pthread_mutex_lock(ph->sh->m_span);
			time = get_time() - ph->philos[i % ph->n_philos].t_span;
			pthread_mutex_unlock(ph->sh->m_span);
			pthread_mutex_lock(ph->sh->m_eat);
			ne += ph->philos[i % ph->n_philos].n_eat;
			pthread_mutex_unlock(ph->sh->m_eat);
			if (is_dead(time, ph, i))
				return (0);
			i++;
		}
		if (!ne)
			return (0);
		usleep(1e2);
	}
}
