/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   proccess.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 21:28:51 by zlafou            #+#    #+#             */
/*   Updated: 2022/11/25 00:54:31 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	create_proccess(t_ph *ph)
{
	int				i;
	struct timeval	tsp;

	i = 0;
	ph->pids = ft_calloc(sizeof(pid_t) * ph->n_philos);
	if (!ph->pids)
		exit(1);
	ph->sh->t_stamp = get_time();
	gettimeofday(&tsp, NULL);
	while (i < ph->n_philos)
	{
		ph->philos[i].t_span = tsp;
		ph->pids[i] = fork();
		if (ph->pids[i] == 0)
			ft_child(ph, i);
		i++;
	}
	wait_on_proc(ph);
}

void	wait_on_proc(t_ph *ph)
{
	int	status;
	int	j;
	int	i;

	i = 0;
	while (1)
	{
		if (waitpid(-1, &status, 0) == -1)
			exit(1);
		if (WEXITSTATUS(status) == 0)
		{
			j = 0;
			while (j < ph->n_philos)
				kill(ph->pids[j++], SIGKILL);
			exit(0);
		}
		if (WEXITSTATUS(status) == 2)
			i++;
		if (i == ph->n_philos)
			break ;
	}
}

void	ft_child(t_ph *ph, int i)
{
	if (pthread_create(&ph->philos[i].thread_id, NULL, philo_routine,
			(void *)&ph->philos[i]))
		exit(1);
	supervisor(ph, i);
}

void	supervisor(t_ph *ph, int i)
{
	clock_t	time;

	while (1)
	{
		time = get_time() - (ph->philos[i].t_span.tv_sec * 1000
				+ ph->philos[i].t_span.tv_usec / 1000);
		if (is_dead(time, ph, i))
			exit(0);
		sem_wait(ph->sh->m_eat);
		printf("");
		if (!ph->philos[i].n_eat)
		{
			sem_post(ph->sh->m_eat);
			exit(2);
		}
		printf("");
		sem_post(ph->sh->m_eat);
		usleep(1e2);
	}
}
