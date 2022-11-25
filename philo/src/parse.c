/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:43:10 by zlafou            #+#    #+#             */
/*   Updated: 2022/11/25 02:18:08 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	arg_validator(char **av, int argn)
{
	int	i;

	i = -1;
	while (av[argn][++i])
	{
		if (!(av[argn][i] >= '0' && av[argn][i] <= '9'))
			return (throwerror());
		if ((av[argn][i] >= '0' && av[argn][i] <= '9') && (av[argn][i
				+ 1] == '-' || av[argn][i + 1] == '+'))
			return (throwerror());
	}
	return (ft_atoi(av[argn]));
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
