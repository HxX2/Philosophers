/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 14:31:20 by zlafou            #+#    #+#             */
/*   Updated: 2022/11/25 00:47:08 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_forks(t_ph *ph)
{
	sem_unlink("forks");
	ph->forks = sem_open("forks", O_CREAT, 0666, ph->n_philos);
	if (ph->forks == SEM_FAILED)
		exit (1);
}

void	init_philos(t_ph *ph)
{
	int	i;

	i = 0;
	ph->philos = ft_calloc(sizeof(t_philo) * ph->n_philos);
	if (!ph->philos)
		exit (1);
	while (i < ph->n_philos)
	{
		ph->philos[i].id = i + 1;
		ph->philos[i].n_eat = ph->sh->n_eat;
		ph->philos[i].sh = ph->sh;
		ph->philos[i].forks = ph->forks;
		i++;
	}
}

void	init_data(t_ph *ph, int ac, char **av)
{
	ph->sh = ft_calloc(sizeof(t_shared));
	if (!ph->sh)
		exit (1);
	ph->n_philos = arg_validator(av, 1);
	ph->sh->t_die = arg_validator(av, 2);
	ph->sh->t_eat = arg_validator(av, 3);
	ph->sh->t_sleep = arg_validator(av, 4);
	if (ac > 5)
		ph->sh->n_eat = arg_validator(av, 5);
	else
		ph->sh->n_eat = -1;
	sem_unlink("m_msg");
	ph->sh->m_msg = sem_open("m_msg", O_CREAT, 0666, 1);
	if (ph->sh->m_msg == SEM_FAILED)
		exit (1);
	sem_unlink("m_eat");
	ph->sh->m_eat = sem_open("m_eat", O_CREAT, 0666, 1);
	if (ph->sh->m_eat == SEM_FAILED)
		exit (1);
}

int	main(int ac, char **av)
{
	t_ph	ph;

	memset(&ph, 0, sizeof(t_ph));
	if (ac < 5)
		return (1);
	init_data(&ph, ac, av);
	init_forks(&ph);
	init_philos(&ph);
	create_proccess(&ph);
}
