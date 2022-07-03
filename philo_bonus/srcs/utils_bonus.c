/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 17:25:01 by jcalon            #+#    #+#             */
/*   Updated: 2022/07/03 21:11:02 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	ft_atoi(const char *nptr)
{
	int	result;
	int	sign;

	result = 0;
	sign = 1;
	while (*nptr && (*nptr == 32 || (*nptr >= 9 && *nptr <= 13)))
		nptr++;
	if (*nptr && (*nptr == '-' || *nptr == '+'))
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (*nptr && *nptr >= '0' && *nptr <= '9')
	{
		result *= 10;
		result += *nptr - 48;
		nptr++;
	}
	return (result * sign);
}

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

void	ft_end(t_arg *args)
{
	int	i;

	i = 0;
	while (i < args->number_of_philosophers)
	{
		kill(args->pid_philo[i], SIGKILL);
		i++;
	}
	free(args->pid_philo);
}
