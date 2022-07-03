/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:42:22 by jcalon            #+#    #+#             */
/*   Updated: 2022/07/03 18:35:25 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	lock_mutex(t_arg *args, int i)
{
	pthread_mutex_lock(&args->philos[i].fed);
	pthread_mutex_lock(&args->print);
}

static int	unlock_mutex(t_arg *args, int i)
{
	pthread_mutex_unlock(&args->philos[i].fed);
	pthread_mutex_unlock(&args->print);
	return (0);
}

static int	dead(t_arg *args, int i)
{
	pthread_mutex_lock(&args->over);
	args->dead = 1;
	pthread_mutex_unlock(&args->over);
	printf("%ld %d died\n", ft_time_diff(args->start), args->philos[i].id);
	unlock_mutex(args, i);
	return (0);
}

int	check_status(t_arg *args)
{
	int	i;
	int	full;

	full = 0;
	while (1)
	{
		i = 0;
		while (i < args->number_of_philosophers)
		{
			lock_mutex(args, i);
			if (args->philos[i].eat_done == 1)
				args->philos[i].eat_done = ++full;
			if (full == args->number_of_philosophers
				&& args->number_of_meal > 0)
				return (unlock_mutex(args, i));
			if (args->philos[i].eat_done == 0
				&& ft_time_diff(args->philos[i].last) > args->time_to_die)
				return (dead(args, i));
			unlock_mutex(args, i);
			usleep(200);
			i++;
		}
	}
	return (0);
}
