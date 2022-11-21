/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:31:20 by zlafou            #+#    #+#             */
/*   Updated: 2022/11/21 23:39:44 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		ph->philos[i].n_eat = ph->sh->n_eat;
		ph->philos[i].sh = ph->sh;
		ph->philos[i].t_span = ph->sh->t_stamp;
		ph->philos[i].l_fork = &ph->forks[i];
		ph->philos[i].r_fork = &ph->forks[(i + 1) % ph->n_philos];
		i++;
	}
}

int	main(int ac, char **av)
{
	t_ph	ph;

	memset(&ph, 0, sizeof(t_ph));
	if (ac < 5)
		return (0);
	ph.sh = ft_calloc(sizeof(t_shared));
	ph.n_philos = arg_validator(av, 1);
	ph.sh->t_die = arg_validator(av, 2);
	ph.sh->t_eat = arg_validator(av, 3);
	ph.sh->t_sleep = arg_validator(av, 4);
	if (ac > 5)
		ph.sh->n_eat = arg_validator(av, 5);
	else
		ph.sh->n_eat = -1;
	ph.sh->m_span = ft_calloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(ph.sh->m_span, NULL);
	ph.sh->m_msg = ft_calloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(ph.sh->m_msg, NULL);
	ph.sh->m_eat = ft_calloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(ph.sh->m_eat, NULL);
	init_forks(&ph);
	init_philos(&ph);
	create_threads(&ph);
	return (supervisor(&ph));
}

void	create_threads(t_ph *ph)
{
	int	i;

	i = 0;
	ph->sh->t_stamp = get_time();
	while (i < ph->n_philos)
	{
		ph->philos[i].t_span = ph->sh->t_stamp;
		pthread_create(&ph->philos[i].thread_id, NULL, philo_routine,
			(void *)&ph->philos[i]);
		i += 2;
	}
	i = 1;
	while (i < ph->n_philos)
	{
		ph->philos[i].t_span = ph->sh->t_stamp;
		pthread_create(&ph->philos[i].thread_id, NULL, philo_routine,
			(void *)&ph->philos[i]);
		i += 2;
	}
}

short	is_dead(clock_t time, t_ph *ph, int i)
{
	if (time > ph->sh->t_die)
	{
		pthread_mutex_lock(ph->sh->m_msg);
		printf("%lu %d died\n", time, ph->philos[i % ph->n_philos].id);
		return (1);
	}
	return (0);
}
