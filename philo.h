/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:22:36 by jcalon            #+#    #+#             */
/*   Updated: 2022/06/29 14:43:23 by jcalon           ###   ########.fr       */
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

struct	s_struct;

typedef struct s_philo {
	int				id;
	int				eat_done;
	int				left_fork;
	int				right_fork;
	long			last;
	struct s_struct	*args;
}				t_philo;

typedef struct s_arg
{
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meal;
	long			start;
	int				philo_id;
	t_philo			*philos;
	pthread_t		*tids;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;
}				t_arg;

int	ft_atoi(const char *nptr);
int	ft_isdigit(int c);

#endif