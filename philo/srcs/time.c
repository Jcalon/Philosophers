/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/03 16:33:54 by jcalon            #+#    #+#             */
/*   Updated: 2022/07/03 16:36:54 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time_diff(long clock)
{
	long	diff;

	diff = ft_time() - clock;
	return (diff);
}

void	ft_usleep(long time)
{
	long	alarm;

	alarm = ft_time() + time;
	while (ft_time() < alarm)
		usleep(time);
}

void	ft_wait(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(philo->args->time_to_eat);
}

long	ft_time(void)
{
	long			now;
	struct timeval	timeval;

	gettimeofday(&timeval, NULL);
	now = (timeval.tv_sec * 1000) + (timeval.tv_usec / 1000);
	return (now);
}
