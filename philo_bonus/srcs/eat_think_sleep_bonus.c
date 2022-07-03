/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eat_think_sleep_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 15:02:44 by jcalon            #+#    #+#             */
/*   Updated: 2022/07/03 21:10:35 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	eat(t_arg *args)
{
	sem_wait(args->forks);
	sem_wait(args->forks);
	sem_wait(args->print);
	printf("%ld %lu has taken a fork\n", \
		ft_time() - args->start, args->philos.id + 1);
	printf("%ld %lu has taken a fork\n", \
		ft_time() - args->start, args->philos.id + 1);
	sem_post(args->print);
	sem_wait(args->print);
	printf("%ld %lu is eating\n", ft_time() - args->start, \
		args->philos.id + 1);
	sem_post(args->print);
	args->philos.last = ft_time();
	args->philos.total_meal_eaten += 1;
	if (args->philos.total_meal_eaten == args->number_of_meal)
		sem_post(args->full);
	ft_usleep(args->time_to_eat);
	sem_post(args->forks);
	sem_post(args->forks);
}

static void	sleep_think(t_arg *args)
{
	sem_wait(args->print);
	printf("%ld %lu is sleeping\n", \
		ft_time() - args->start, args->philos.id + 1);
	sem_post(args->print);
	ft_usleep(args->time_to_sleep);
	sem_wait(args->print);
	printf("%ld %lu is thinking\n", \
		ft_time() - args->start, args->philos.id + 1);
	sem_post(args->print);
}

static void	*eat_think_sleep(void *arg)
{
	t_arg	*philo;

	philo = (t_arg *)arg;
	philo->start = ft_time();
	while (1)
	{
		eat(philo);
		sleep_think(philo);
	}
	return (NULL);
}

static int	init_philo(t_arg *args)
{
	args->philos.last = ft_time();
	if (pthread_create(&args->status, NULL, &check_status, args))
	{
		sem_post(args->dead);
	}
	pthread_detach(args->status);
	return (0);
}

int	philo(t_arg *args)
{
	int	i;

	i = 0;
	args->start = ft_time();
	while (i < args->number_of_philosophers)
	{
		args->philos.id = i;
		args->pid_philo[i] = fork();
		if (args->pid_philo[i] == -1)
		{
			while (--i >= 0)
				kill(args->pid_philo[i], SIGKILL);
			return (1);
		}
		else
		{
			if (init_philo(args))
				return (1);
			eat_think_sleep(args);
		}
		i++;
	}
	sem_wait(args->dead);
	return (0);
}
