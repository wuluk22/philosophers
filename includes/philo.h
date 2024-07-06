/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:09:07 by clegros           #+#    #+#             */
/*   Updated: 2024/04/16 19:09:10 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <string.h>
# include <stdatomic.h>

struct	s_data;

typedef struct s_philo
{
	int				id;
	long			last_eat;
	int				nbr_eat;
	int				left_fork;
	int				right_fork;
	int				verif;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				nbr_philo;
	unsigned int	t_to_die;
	unsigned int	t_to_eat;
	unsigned int	t_to_sleep;
	int				nb_of_time;
	int				dead;
	atomic_int		eat_en;
	int				all_eat;
	time_t			start_time;
	t_philo			*philo;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_dead;
	pthread_mutex_t	m_full;
	pthread_mutex_t	*forks;
}	t_data;

long long	ft_atol(char *av);
int			check_value(char **av);
void		ft_sleep(t_data *data, time_t end);
int			ft_strcmp(char *s1, char *s2);
time_t		get_time(t_data *data);
void		*eat(void *philo_pointer);
void		*routine(void *data_pointer);

#endif
