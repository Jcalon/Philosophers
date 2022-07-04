/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:13:23 by jcalon            #+#    #+#             */
/*   Updated: 2022/07/04 11:48:12 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_args(char	**argv)
{
	size_t	i;
	size_t	j;

	i = 1;
	while (argv[i])
	{
		if (!ft_atoi(argv[i]))
			return (1);
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	init_args(t_arg *args, int argc, char **argv)
{
	memset(args, 0, sizeof(t_arg));
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->number_of_meal = ft_atoi(argv[5]);
	else
		args->number_of_meal = 0;
	if (args->number_of_philosophers < 1 || args->time_to_die < 1
		|| args->time_to_eat < 1 || args->time_to_sleep < 1
		|| (argc == 6 && args->number_of_meal < 1))
		return (1);
	return (0);
}

static int	init_sem(t_arg *args)
{
	args->pid_philo = malloc(sizeof(pid_t) * args->number_of_philosophers);
	if (args->pid_philo == NULL)
		return (1);
	memset(args->pid_philo, 0, sizeof(pid_t) * args->number_of_philosophers);
	sem_unlink("forks");
	sem_unlink("print");
	sem_unlink("dead");
	sem_unlink("full");
	args->forks = sem_open("forks", O_CREAT
			| O_EXCL, S_IRWXU, args->number_of_philosophers);
	args->print = sem_open("print", O_CREAT | O_EXCL, S_IRWXU, 1);
	args->dead = sem_open("dead", O_CREAT | O_EXCL, S_IRWXU, 0);
	if (args->number_of_meal)
		args->full = sem_open("full", O_CREAT | O_EXCL, S_IRWXU, 0);
	if (args->number_of_meal)
	{
		if (pthread_create(&args->status, NULL, &check_meals, args))
		{
			free(args->pid_philo);
			return (1);
		}
		pthread_detach(args->status);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_arg	args;

	if (argc < 5 || argc > 6)
	{
		printf("Incorrect number of arguments\n");
		return (EXIT_FAILURE);
	}
	if (check_args(argv))
	{
		printf("Error, write : ./philo : number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep [number_of_times_each_must_eat]\n");
		return (EXIT_FAILURE);
	}
	if (init_args(&args, argc, argv) == 1)
		return (EXIT_FAILURE);
	if (init_sem(&args))
		return (EXIT_FAILURE);
	if (philo(&args))
		return (EXIT_FAILURE);
	ft_end(&args);
	return (0);
}
