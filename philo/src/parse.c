/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 12:43:10 by zlafou            #+#    #+#             */
/*   Updated: 2022/10/28 09:29:29 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int arg_validator(char **av, int argn)
{
	int	i;

	i = -1;
	while (av[argn][++i])
	{
		if (!(av[argn][i] >= '0' && av[argn][i] <= '9'))
			throwerror();
		if ((av[argn][i] >= '0' && av[argn][i] <= '9') && (av[argn][i + 1] == '-'
				|| av[argn][i + 1] == '+'))
			throwerror();
	}
	return (ft_atoi(av[argn]));
}