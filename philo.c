/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:13:23 by jcalon            #+#    #+#             */
/*   Updated: 2022/06/23 14:13:36 by jcalon           ###   ########.fr       */
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

int	init_args(t_arg *args, int argc, char **argv)
{
	args->number_of_philosophers = ft_atoi(argv[1]);
	args->time_to_die = ft_atoi(argv[2]);
	args->time_to_eat = ft_atoi(argv[3]);
	args->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		args->number_of_meal = ft_atoi(argv[5]);
	else
		args->number_of_meal = -1;
	args->dead = 0;
	return (0);
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
	pthread_mutex_init(args.token, NULL);
	pthread_mutex_init(args.phil_with_token, NULL);
	i = 0;
	while (i < args.number_of_philosophers)
	{
		pthread_mutex_init();
	}
}
