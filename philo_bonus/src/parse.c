/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:43:10 by zlafou            #+#    #+#             */
/*   Updated: 2022/11/24 04:20:23 by zlafou           ###   ########.fr       */
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
			throwerror();
		if ((av[argn][i] >= '0' && av[argn][i] <= '9') && (av[argn][i
				+ 1] == '-' || av[argn][i + 1] == '+'))
			throwerror();
	}
	return (ft_atoi(av[argn]));
}

short	is_dead(clock_t time, t_ph *ph, int i)
{
	if (time > ph->sh->t_die)
	{
		sem_wait(ph->sh->m_msg);
		printf("%lu %d died\n", time, ph->philos[i].id);
		return (1);
	}
	return (0);
}
