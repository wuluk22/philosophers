/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_philo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:21:11 by clegros           #+#    #+#             */
/*   Updated: 2024/07/10 18:21:13 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int	main(int ac, char **av)
{
	t_data		data;
	int		i;

	i = 0;
	if (ac != 5 && ac != 6)
		return(write(1, "Error: 5 or 6\n", 14), 1);
	if (atoi(av[1]) <= 0 || atoi(av[1]) > 200)
		return(write(1, "Error: 0 to 200\n", 16), 1);
	// if (!is_number)
	parse_input(&data, av);
	data_init(&data);
	dinner_start(&data);
	//clean(&data);
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
		philosophers[i].state = THINKING;
		pthread_create(&threads[i], NULL, routine, &philosophers[i]);
		i++;
	}
	i = 0;
	while (i < data.nbr_philo)
		pthread_join(threads[i], NULL);
	free(data.forks);
	return (0);
}*/

int	main(int ac, char **av)
{
	t_data	data;

	if (5 == ac || 6 == ac)
	{
		parse_input(&data, av);
		data_init(&data);
		start_dinner(&data);
		clean(&data);
	}
	else
	{
		error_exit("Wrong input.\n"
			"Right input is: ./philo 5 300 150 150 [4]");
	}
}
