/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:31:20 by zlafou            #+#    #+#             */
/*   Updated: 2022/11/22 19:19:13 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_forks(t_ph *ph)
{
	int	i;

	ph->forks = ft_calloc(sizeof(pthread_mutex_t) * ph->n_philos);
	if (!ph->forks)
		return (1);
	i = 0;
	while (i < ph->n_philos)
	{
		pthread_mutex_init(&ph->forks[i], NULL);
		i++;
	}
	return (0);
}

int	init_philos(t_ph *ph)
{
	int	i;

	i = 0;
	ph->philos = ft_calloc(sizeof(t_philo) * ph->n_philos);
	if (!ph->philos)
		return (1);
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
	return (0);
}

int	init_data(t_ph *ph, int ac, char **av)
{
	ph->sh = ft_calloc(sizeof(t_shared));
	if (!ph->sh)
		return (1);
	ph->n_philos = arg_validator(av, 1);
	ph->sh->t_die = arg_validator(av, 2);
	ph->sh->t_eat = arg_validator(av, 3);
	ph->sh->t_sleep = arg_validator(av, 4);
	if (ac > 5)
		ph->sh->n_eat = arg_validator(av, 5);
	else
		ph->sh->n_eat = -1;
	ph->sh->m_span = ft_calloc(sizeof(pthread_mutex_t));
	if (!ph->sh->m_span)
		return (1);
	pthread_mutex_init(ph->sh->m_span, NULL);
	ph->sh->m_msg = ft_calloc(sizeof(pthread_mutex_t));
	if (!ph->sh->m_msg)
		return (1);
	pthread_mutex_init(ph->sh->m_msg, NULL);
	ph->sh->m_eat = ft_calloc(sizeof(pthread_mutex_t));
	if (!ph->sh->m_eat)
		return (1);
	pthread_mutex_init(ph->sh->m_eat, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	t_ph	ph;

	memset(&ph, 0, sizeof(t_ph));
	if (ac < 5)
		return (1);
	if (init_data(&ph, ac, av))
		return (1);
	if (init_forks(&ph))
		return (1);
	if (init_philos(&ph))
		return (1);
	if (create_threads(&ph))
		return (1);
	return (supervisor(&ph));
}

int	create_threads(t_ph *ph)
{
	int	i;

	i = 0;
	ph->sh->t_stamp = get_time();
	while (i < ph->n_philos)
	{
		ph->philos[i].t_span = ph->sh->t_stamp;
		if (pthread_create(&ph->philos[i].thread_id, NULL, philo_routine,
				(void *)&ph->philos[i]))
			return (1);
		i += 2;
	}
	i = 1;
	while (i < ph->n_philos)
	{
		ph->philos[i].t_span = ph->sh->t_stamp;
		if (pthread_create(&ph->philos[i].thread_id, NULL, philo_routine,
				(void *)&ph->philos[i]))
			return (1);
		i += 2;
	}
	return (0);
}
