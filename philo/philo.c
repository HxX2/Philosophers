/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:31:20 by zlafou            #+#    #+#             */
/*   Updated: 2022/11/25 00:12:50 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_args(t_ph *ph, char **av, int ac)
{
	ph->n_philos = arg_validator(av, 1);
	if (ph->n_philos == -1)
		return (1);
	ph->sh->t_die = arg_validator(av, 2);
	if (ph->sh->t_die == (clock_t)-1)
		return (1);
	ph->sh->t_eat = arg_validator(av, 3);
	if (ph->n_philos == -1)
		return (1);
	ph->sh->t_sleep = arg_validator(av, 4);
	if (ph->n_philos == -1)
		return (1);
	if (ac > 5)
	{
		ph->sh->n_eat = arg_validator(av, 5);
		if (ph->n_philos == -1)
			return (1);
	}
	else
		ph->sh->n_eat = -1;
	return (0);
}

int	init_data(t_ph *ph, int ac, char **av)
{
	ph->sh = ft_calloc(sizeof(t_shared));
	if (!ph->sh)
		return (1);
	if (init_args(ph, av, ac))
		return (1);
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
