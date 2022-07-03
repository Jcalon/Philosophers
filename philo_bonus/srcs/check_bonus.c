/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:42:22 by jcalon            #+#    #+#             */
/*   Updated: 2022/07/03 21:18:48 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_meals(void *arg)
{
	t_arg	*args;
	int		i;

	args = arg;
	i = 0;
	sem_wait(args->print);
	while (i < args->number_of_philosophers)
	{
		sem_post(args->print);
		sem_wait(args->full);
		sem_wait(args->print);
		i++;
	}
	sem_post(args->dead);
	return (NULL);
}

void	*check_status(void *arg)
{
	t_arg	*args;
	long	now;

	args = arg;
	while (1)
	{
		now = ft_time();
		if (now - args->philos.last > args->time_to_die)
		{
			sem_wait(args->print);
			printf("%ld %lu died\n", \
				ft_time() - args->start, args->philos.id + 1);
			sem_post(args->dead);
			exit(0);
		}
	}
	return (NULL);
}

void	ft_usleep(long time)
{
	long	alarm;

	alarm = ft_time() + time;
	while (ft_time() < alarm)
		usleep(time);
}

long	ft_time(void)
{
	long			now;
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	now = (timeval.tv_sec * 1000) + (timeval.tv_usec / 1000);
	return (now);
}
