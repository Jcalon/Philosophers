/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:42:22 by jcalon            #+#    #+#             */
/*   Updated: 2022/07/01 17:12:52 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time_diff(long clock)
{
	long	diff;

	diff = ft_time() - clock;
	return (diff);
}

void	custom_printf(char *s, t_philo *philo)
{
	pthread_mutex_lock(&philo->args->print);
	if (philo->args->dead != 1)
		printf("%ld %d %s\n", ft_time_diff(philo->args->start), philo->id, s);
	pthread_mutex_unlock(&philo->args->print);
}

int		check_status(t_arg *args)
{
	int	i;
	int	full;
	
	full = 0;
	while (1)
	{
		i = 0;
		while (i < args->number_of_philosophers)
		{
			pthread_mutex_lock(&args->philos[i].fed);
			pthread_mutex_lock(&args->print);
			if (args->philos[i].eat_done == 1)
				args->philos[i].eat_done = ++full;
			if (full == args->number_of_philosophers && args->number_of_meal > 0)
			{
				pthread_mutex_unlock(&args->philos[i].fed);
				pthread_mutex_unlock(&args->print);
				return (0);	
			}
			if (args->philos[i].eat_done == 0
				&& ft_time_diff(args->philos[i].last) > args->time_to_die)
			{
				pthread_mutex_lock(&args->over);
				args->dead = 1;
				pthread_mutex_unlock(&args->over);
				printf("%ld %d died\n", ft_time_diff(args->start), args->philos[i].id);
				pthread_mutex_unlock(&args->philos[i].fed);
				pthread_mutex_unlock(&args->print);
				return (0);
			}
			pthread_mutex_unlock(&args->philos[i].fed);
			pthread_mutex_unlock(&args->print);
			i++;
			usleep(200);
		}
	}
	return (0);
}