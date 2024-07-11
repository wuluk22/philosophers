/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:20:16 by clegros           #+#    #+#             */
/*   Updated: 2024/07/10 18:20:18 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo, bool pre_simulation)
{
	long	t_eat;
	long	t_sleep;
	long	t_think;

	if (!pre_simulation)
		write_status(THINKING, philo);
	if (philo->data->nbr_philo % 2 == 0)
		return ;
	t_eat = philo->data->t_to_eat;
	t_sleep = philo->data->t_to_sleep;
	t_think = (t_eat * 2) - t_sleep;
	if (t_think < 0)
		t_think = 0;
	precise_usleep(t_think * 0.42, philo->data);
}

void	*only_one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	increase_long(&philo->data->data_mutex,
		&philo->data->running_threads);
	write_status(TAKE_FIRST_FORK, philo);
	while (!simulation_end(philo->data))
		precise_usleep(200, philo->data);
	return (NULL);
}

static void	eat(t_philo *philo)
{
	safe_mutex(&philo->right_fork->fork, LOCK);
	write_status(TAKE_FIRST_FORK, philo);
	safe_mutex(&philo->left_fork->fork, LOCK);
	write_status(TAKE_SECOND_FORK, philo);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	philo->meal_count++;
	write_status(EATING, philo);
	precise_usleep(philo->data->t_to_eat, philo->data);
	if (philo->data->lmt_number_meals > 0
		&& philo->meal_count == philo->data->lmt_number_meals)
		set_bool(&philo->philo_mutex, &philo->full, true);
	safe_mutex(&philo->right_fork->fork, UNLOCK);
	safe_mutex(&philo->left_fork->fork, UNLOCK);
}

void	*dinner_simulation(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	wait_all_threads(philo->data);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECOND));
	increase_long(&philo->data->data_mutex,
		&philo->data->running_threads);
	fairly_synchronize_philos(philo);
	while (!simulation_end(philo->data))
	{
		if (get_bool(&philo->philo_mutex, &philo->full))
			break ;
		eat(philo);
		write_status(SLEEPING, philo);
		precise_usleep(philo->data->t_to_sleep, philo->data);
		thinking(philo, false);
	}
	return (NULL);
}

void	start_dinner(t_data *data)
{
	int			i;

	i = -1;
	if (data->lmt_number_meals == 0)
		return ;
	else if (data->nbr_philo == 1)
		safe_thread(&data->philo[0].thread_id, only_one_philo,
			&data->philo[0], CREATE);
	else
		while (++i < data->nbr_philo)
			safe_thread(&data->philo[i].thread_id, dinner_simulation,
				&data->philo[i], CREATE);
	safe_thread(&data->monitor, monitor_dinner, data, CREATE);
	data->start_time = get_time(MILLISECOND);
	set_bool(&data->data_mutex, &data->all_threads_ready, true);
	i = -1;
	while (++i < data->nbr_philo)
		safe_thread(&data->philo[i].thread_id, NULL, NULL, JOIN);
	set_bool(&data->data_mutex, &data->end_time, true);
	safe_thread(&data->monitor, NULL, NULL, JOIN);
}
