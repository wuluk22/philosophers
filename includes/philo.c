/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 19:08:59 by clegros           #+#    #+#             */
/*   Updated: 2024/04/16 19:09:01 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*static void	*first_philo(void *arg)
{
	(void)arg;
	return (arg);
}*/

/*static void	*print_tid(void *tid)
{
	printf("Thread ID: %p\n", (void *)tid);
	return (tid);
}

static int	philo_init(t_data *data)
{
	pthread_t	first_philo;
	int			status;

	(void)data;
	status = pthread_create(&first_philo, NULL, print_tid, &first_philo);
	pthread_join(first_philo, NULL);
	return (0);
}*/

int	main(int ac, char **av)
{
	t_data		data;
	t_philo		*philosophers;
	pthread_t	*threads;
	int		i;

	i = 0;
	if (ac != 5 && ac != 6)
		return(write(1, "Error: 5 or 6\n", 14), 1);
	if (atoi(av[1]) <= 0 || atoi(av[1]) > 200)
		return(write(1, "Error: 0 to 200\n", 16), 1);
	// if (!is_number)
	data.nbr_philo = atoi(av[1]);
	data.t_to_die = atoi(av[2]);
	data.t_to_eat = atoi(av[3]);
	data.t_to_sleep = atoi(av[4]);
	if (ac == 6)
		data.nb_of_time = atoi(av[5]);
	else
		data.nb_of_time = -1;
	data.forks = malloc(sizeof(pthread_mutex_t) * data.nbr_philo);
	if (!data.forks)
		return (write(1, "Error: malloc\n", 14), 1);
	while (i < data.nbr_philo)
		pthread_mutex_init(&data.forks[i++], NULL);
	pthread_mutex_init(&data.m_print, NULL);
	philosophers = malloc(sizeof(t_philo) * data.nbr_philo);
	threads = malloc(sizeof(pthread_t) * data.nbr_philo);
	if (!philosophers || !threads)
		return (write(1, "Error: Malloc\n", 14), 1);
	i = 0;
	while (i < data.nbr_philo)
	{
		philosophers[i].id = i;
		philosophers[i].left_fork = i;
		philosophers[i].right_fork = (i + 1) % data.nbr_philo;
		philosophers[i].data = &data;
		pthread_create(&threads[i], NULL, routine, &philosophers[i]);
		i++;
	}
	i = 0;
	while (i < data.nbr_philo)
		pthread_join(threads[i], NULL);
	free(data.forks);
	free(philosophers);
	free(threads);
	return (0);
}
