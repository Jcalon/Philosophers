/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:22:36 by jcalon            #+#    #+#             */
/*   Updated: 2022/06/29 12:42:59 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <strings.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_arg
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meal;
	int				dead;
	int				philo_id;
	time_t			start_time;
	pthread_mutex_t	*forks;
	pthread_t		*tids;
	pthread_mutex_t	*token;
	pthread_mutex_t	*phil_with_token;
}				t_arg;

int	ft_atoi(const char *nptr);
int	ft_isdigit(int c);

#endif