/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_think_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:02:44 by jcalon            #+#    #+#             */
/*   Updated: 2022/06/29 15:48:21 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_time(void)
{
	long	now;
	struct timeva1 time;
	{
		/* data */
	};
	
}

static void ft_usleep(long time)
{
	long	alarm;

	alarm = ft_time() + time;
	while (ft_time() < alarm)
		usleep(time);
}

static void *eat_think_sleep(void *arg)
{
	t_philo *philo;
	int		all_full;

	philo = (t_philo *)arg;
	all_full = 0;
	while (1)
	{
		ft_wait(philo->id);
		pthread_mutex_lock(&philo->args->forks[philo->left_fork]);
		printf("fourchette", philo);
		pthread_mutex_lock(&philo->args->forks[philo->right_fork]);
		printf("fourchette", philo);
		printf("manger", philo);
		philo->last = ft_time();
		ft_usleep(philo->args->time_to_eat);
		pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
		pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
		if (philo->args->number_of_meal == ++all_full)
			break ;
		printf("dodo", philo);
		ft_usleep(philo->args->time_to_sleep);
		printf("pnser", philo);
	}
	philo->eat_done = 1;
	return (NULL);
}

int	create_threads(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (pthread_create(&args->tids[i], NULL,
				&eat_think_sleep, &args->philos[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}