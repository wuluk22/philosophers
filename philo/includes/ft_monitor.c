/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dead.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:20:23 by clegros           #+#    #+#             */
/*   Updated: 2024/07/10 18:20:24 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static bool	philo_died(t_philo *philo)
{
	long	passed;
	long	t_to_die;

	if (get_bool(&philo->philo_mutex, &philo->full))
		return (false);
	passed = get_time(MILLISECOND) - get_long(&philo->philo_mutex,
			&philo->last_meal_time);
	t_to_die = philo->data->t_to_die / 1e3;
	if (passed > t_to_die)
		return (true);
	return (false);
}

static bool	check_philo_state(t_data *n_data, int *i, bool *all_full)
{
	if (philo_died(n_data->philo))
	{
		set_bool(&n_data->data_mutex, &n_data->end_time, true);
		write_status(DIED, n_data->philo + *i);
		return (true);
	}
	if (!get_bool(&n_data->philo[*i].philo_mutex, &n_data->philo[*i].full))
		*all_full = false;
	return (false);
}

static void	check_philos(t_data *n_data)
{
	int		i;
	bool	all_full;

	while (!simulation_end(n_data))
	{
		i = -1;
		all_full = true;
		while (++i < n_data->nbr_philo && !simulation_end(n_data))
			if (check_philo_state(n_data, &i, &all_full))
				return ;
		if (all_full)
		{
			set_bool(&n_data->data_mutex, &n_data->end_time, true);
			break ;
		}
		precise_usleep(1000, n_data);
	}
}

void	*monitor_dinner(void *data)
{
	t_data	*n_data;

	n_data = (t_data *)data;
	while (!all_threads_running(&n_data->data_mutex, &n_data->running_threads,
			n_data->nbr_philo))
		;
	check_philos(n_data);
	return (NULL);
}
