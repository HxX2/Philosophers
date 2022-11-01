/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zlafou <zlafou@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 07:05:18 by zlafou            #+#    #+#             */
/*   Updated: 2022/11/01 07:03:13 by zlafou           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_atoi(const char *str)
{
	unsigned long	res;
	int				s;
	int				i;

	res = 0;
	s = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			s *= -1;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res * s);
}

void	throwerror(void)
{
	write(1, "\033[0;31m\033[1mError\033[0;0m\n", 24);
	exit(1);
}

unsigned long	get_time()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_usleep(unsigned long ms)
{
	unsigned long time1;
	unsigned long time2;

	time1 = get_time();
	time2 = get_time();
	while (time2 - time1 < ms)
	{
		usleep(10);
		time2 = get_time();
	}
}

void	*ft_calloc(size_t n)
{
	void		*ptr;

	ptr = malloc(n);
	if (!ptr)
		return (0);
	while (n)
		((unsigned char *)ptr)[--n] = 0;
	return (ptr);
}

void	msg(unsigned long ts, int id, char *msg, pthread_mutex_t *mutex)
{
	pthread_mutex_lock(mutex);
	printf("%lu %d %s\n", ts, id, msg);
	pthread_mutex_unlock(mutex);
}