/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 23:00:49 by zlafou            #+#    #+#             */
/*   Updated: 2022/11/24 23:22:29 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	take_forks(t_philo *philo)
{
	sem_wait(philo->forks);
	sem_wait(philo->forks);
	msg(get_time() - philo->sh->t_stamp, philo->id, "has taken a r fork",
		philo->sh->m_msg);
	msg(get_time() - philo->sh->t_stamp, philo->id, "has taken a l fork",
		philo->sh->m_msg);
}

void	eat(t_philo *philo)
{
	msg(get_time() - philo->sh->t_stamp, philo->id, "is eating",
		philo->sh->m_msg);
}

void	*philo_routine(void *targ)
{
	t_philo	*philo;

	philo = (t_philo *)targ;
	while (1)
	{
		take_forks(philo);
		eat(philo);
		philo->t_span = get_time();
		ft_usleep(philo->sh->t_eat);
		sem_post(philo->forks);
		sem_post(philo->forks);
		sem_wait(philo->sh->m_eat);
		if (philo->n_eat)
			philo->n_eat--;
		sem_post(philo->sh->m_eat);
		msg(get_time() - philo->sh->t_stamp, philo->id, "is sleeping",
			philo->sh->m_msg);
		ft_usleep(philo->sh->t_sleep);
		msg(get_time() - philo->sh->t_stamp, philo->id, "is thinking",
			philo->sh->m_msg);
	}
	return (NULL);
}

void	msg(unsigned long ts, int id, char *msg, sem_t *semaphore)
{
	sem_wait(semaphore);
	printf("%lu %d %s\n", ts, id, msg);
	sem_post(semaphore);
}
