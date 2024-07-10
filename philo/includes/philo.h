/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:22:04 by clegros           #+#    #+#             */
/*   Updated: 2024/07/10 18:22:05 by clegros          ###   ########.fr       */
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
# include <stdbool.h>
# include <stdatomic.h>
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define DEBUG_MODE 0
# ifndef PHILO_MAX
#  define PHILO_MAX 200 
# endif

typedef enum e_opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef enum e_time_code
{
	SECOND,
	MILLISECOND,
	MICROSECOND,
}	t_time_code;

typedef pthread_mutex_t	t_mtx;

typedef struct s_fork
{
	t_mtx	fork;
	int		fork_id;
}	t_fork;

typedef struct s_philo
{
	int				id;
	long			meal_count;
	bool			full;
	long			last_meal_time;
	int				nbr_eat;
	t_fork			*left_fork;
	t_fork			*right_fork;
	int				state;
	pthread_t		thread_id;
	t_mtx			philo_mutex;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int					nbr_philo;
	unsigned int		t_to_die;
	unsigned int		t_to_eat;
	unsigned int		t_to_sleep;
	int					lmt_number_meals;
	long				start_time;
	bool				end_time;
	bool				all_threads_ready;
	long				running_threads;
	//int				dead;
	//atomic_int		eat_en;
	//int				all_eat;
	t_philo				*philo;
	t_mtx				data_mutex;
	t_mtx				m_print;
	t_mtx				m_dead;
	t_mtx				m_full;
	t_fork				*forks;
	pthread_t			monitor;
}	t_data;

typedef enum e_status
{
	EATING,
	SLEEPING,
	THINKING,
	TAKE_FIRST_FORK,
	TAKE_SECOND_FORK,
	DIED,
	EINVAL,
	EDEADLK,
	EPERM,
	ENOMEM,
	EBUSY,
	EAGAIN,
	ESRCH,
}	t_philo_status;

//--- ft_clean.c
void	clean(t_data *data);

//--- ft_data.c
void	thinking(t_philo *philo, bool pre_simulation);
void	*only_one_philo(void *arg);
void	*dinner_simulation(void *data);
void	start_dinner(t_data *data);

//--- ft_dead.c
void	*monitor_dinner(void *data);

//--- ft_get_set.c
void	set_bool(t_mtx *mutex, bool *dest, bool value);
bool	get_bool(t_mtx *mutex, bool *value);
void	set_long(t_mtx *mutex, long *dest, long value);
long	get_long(t_mtx *mutex, long *value);
bool	simulation_end(t_data *data);

//--- ft_init.c
void	data_init(t_data *data);

//--- ft_parsing.c
long	ft_atol(const char *str);
void	parse_input(t_data *data, char **av);

//--- ft_print.c
void	write_status(t_philo_status status, t_philo *philo);

//--- ft_safe.c
void	*safe_malloc(size_t bytes);
void	safe_thread(pthread_t *thread, void *(*foo)(void *),
			void *data, t_opcode opcode);
void	safe_mutex(t_mtx *mutex, t_opcode opcode);

//--- ft_sync_utils.c
void	increase_long(t_mtx *mutex, long *value);
void	wait_all_threads(t_data *data);
void	fairly_synchronize_philos(t_philo *philo);
bool	all_threads_running(t_mtx *mutex, long *threads,
			long philo_nbr);

//--- ft_utils.c
long	get_time(t_time_code time_code);
void	error_exit(const char *error);
void	precise_usleep(long usec, t_data *data);

//int			check_value(char **av);
//void		ft_sleep(t_data *data, time_t end);
//void		*routine(void *data_pointer);

#endif
