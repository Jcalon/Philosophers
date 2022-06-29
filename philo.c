/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:13:23 by jcalon            #+#    #+#             */
/*   Updated: 2022/06/29 15:07:41 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			if (!ft_is_digit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

static int	init_args(t_arg *args, int argc, char **argv)
{
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->number_of_meal = ft_atoi(argv[5]);
	else
		args->number_of_meal = -1;
	if (args->number_of_philosophers < 1 || args->time_to_die < 1
		|| args->time_to_eat < 1 || args->time_to_sleep < 1
		|| (argc == 6 && args->number_of_meal < 1))
		return (1);
	return (0);
}

static int	init_struct(t_arg *args)
{
	args->philos = (t_philo *)malloc(sizeof(t_philo) * args->number_of_philosophers);
	if (args->philos == NULL)
		return (1);
	args->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * args->number_of_philosophers);
	if (args->forks == NULL)
	{
		free(args->philos);
		return (1);
	}
	args->tids = (pthread_t *)malloc(sizeof(pthread_t) * args->number_of_philosophers);
	if (args->tids == NULL)
	{
		free(args->philos);
		free(args->forks);
		return (1);
	}
	return (0);
}

static void	init_mutex(t_arg *args)
{
	size_t	i;

	i = 0;
	args->start =
}

int	main(int argc, char *argv[])
{
	t_arg	args;
	size_t	i;

	if (argc < 5 || argc > 6)
	{
		printf("Incorrect number of arguments\n");
		return (EXIT_FAILURE);
	}
	if (!check_args(argv))
	{
		printf("Error, write : ./philo : number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (EXIT_FAILURE);
	}
	if (init_args(&args, argc, argv) == 1)
		return (EXIT_FAILURE);
	if (init_struct(&args))
		return (EXIT_FAILURE);
	init_mutex(&args);
}