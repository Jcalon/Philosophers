/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcalon <jcalon@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 16:22:36 by jcalon            #+#    #+#             */
/*   Updated: 2022/07/03 21:09:15 by jcalon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <strings.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <string.h>

struct	s_arg;

typedef struct s_philo {
	size_t			id;
	int				eat_done;
	size_t			total_meal_eaten;
	pthread_t		status_tid;
	time_t			last;
}				t_philo;

typedef struct s_arg
{
	int				number_of_philosophers;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	size_t			number_of_meal;
	time_t			start;
	t_philo			philos;
	pthread_t		status;
	pid_t			*pid_philo;
	sem_t			*print;
	sem_t			*forks;
	sem_t			*dead;
	sem_t			*full;
}					t_arg;

int		philo(t_arg *args);
void	*check_status(void *arg);
void	*check_meals(void *arg);

int		ft_atoi(const char *nptr);
int		ft_isdigit(int c);
void	ft_end(t_arg *args);

long	ft_time(void);
void	ft_usleep(long time);

#endif