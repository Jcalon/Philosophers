/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_think_sleep.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:02:44 by jcalon            #+#    #+#             */
/*   Updated: 2022/07/01 17:57:12 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void ft_usleep(long time)
{
	long	alarm;

	alarm = ft_time() + time;
	while (ft_time() < alarm)
		usleep(time);
}

static void	ft_wait(t_philo *philo)
{
	if (philo->id % 2 == 0)
		usleep(philo->args->time_to_eat);
}

long	ft_time(void)
{
	long	now;
	struct timeval timeval;
	
	gettimeofday(&timeval, NULL);
	now = (timeval.tv_sec * 1000) + (timeval.tv_usec / 1000);
	return (now);
}

static void test(t_philo *philo)
{
		pthread_mutex_lock(&philo->args->forks[philo->right_fork]);
		custom_printf("has taken a fork", philo);
		pthread_mutex_lock(&philo->args->forks[philo->left_fork]);
		custom_printf("has taken a fork", philo);
		custom_printf("is eating", philo);
		pthread_mutex_lock(&philo->fed);
		philo->last = ft_time();
		pthread_mutex_unlock(&philo->fed);
		ft_usleep(philo->args->time_to_eat);
		pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
		pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
}

static int	mort(t_philo* philo)
{
	pthread_mutex_lock(&philo->args->over);
	if (philo->args->dead != 1)
	{
		pthread_mutex_unlock(&philo->args->over);
		return (1);
	}
	pthread_mutex_unlock(&philo->args->over);
	return (0);
}

static void *eat_think_sleep(void *arg)
{
	t_philo *philo;
	int		all_full;

	philo = (t_philo *)arg;
	all_full = 0;
	while (mort(philo) == 1)
	{
		ft_wait(philo);
		if (philo->right_fork == 0)
			test(philo);
		else
		{
			pthread_mutex_lock(&philo->args->forks[philo->left_fork]);
			custom_printf("has taken a fork", philo);
			pthread_mutex_lock(&philo->args->forks[philo->right_fork]);
			custom_printf("has taken a fork", philo);
			custom_printf("is eating", philo);
			pthread_mutex_lock(&philo->fed);
			philo->last = ft_time();
			pthread_mutex_unlock(&philo->fed);
			ft_usleep(philo->args->time_to_eat);
			pthread_mutex_unlock(&philo->args->forks[philo->right_fork]);
			pthread_mutex_unlock(&philo->args->forks[philo->left_fork]);
		}
		if (philo->args->number_of_meal == ++all_full)
			break;
		custom_printf("is sleeping", philo);
		ft_usleep(philo->args->time_to_sleep);
		custom_printf("is thinking", philo);
	}
	pthread_mutex_lock(&philo->fed);
	philo->eat_done = 1;
	pthread_mutex_unlock(&philo->fed);
	return (NULL);
}

int	create_threads(t_arg *args)
{
	int	i;

	i = 0;
	if (args->number_of_philosophers == 1)
	{
		printf("%ld %d has taken a fork\n", ft_time_diff(args->start), args->philos[i].id);
		ft_usleep(args->time_to_die);
		printf("%ld %d died\n", ft_time_diff(args->start), args->philos[i].id);
		ft_end(args);
		return (0);
	}
	while (i < args->number_of_philosophers)
	{
		if (pthread_create(&args->tids[i], NULL,
				&eat_think_sleep, &args->philos[i]) != 0)
			return (1);
		i++;
	}
	if (!check_status(args))
		ft_end(args);
	return (0);
}