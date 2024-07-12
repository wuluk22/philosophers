/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:20:44 by clegros           #+#    #+#             */
/*   Updated: 2024/07/10 18:20:46 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_forks(t_philo *philo, t_fork *forks, int position)
{
	int	nbr_philo;

	nbr_philo = philo->data->nbr_philo;
	philo->right_fork = &forks[(position + 1) % nbr_philo];
	philo->left_fork = &forks[position];
	if (philo->id % 2 == 0)
	{
		philo->right_fork = &forks[position];
		philo->left_fork = &forks[(position + 1) % nbr_philo];
	}
}

static void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->nbr_philo)
	{
		philo = data->philo + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meal_count = 0;
		philo->data = data;
		safe_mutex(&philo->philo_mutex, INIT);
		assign_forks(philo, data->forks, i);
	}
}

void	data_init(t_data *data)
{
	int	i;

	i = -1;
	data->end_time = false;
	data->all_threads_ready = false;
	data->running_threads = 0;
	data->philo = safe_malloc(data->nbr_philo * sizeof(t_philo));
	data->forks = safe_malloc(data->nbr_philo * sizeof(t_fork));
	safe_mutex(&data->m_print, INIT);
	safe_mutex(&data->data_mutex, INIT);
	while (++i < data->nbr_philo)
	{
		safe_mutex(&data->forks[i].fork, INIT);
		data->forks[i].fork_id = i;
	}
	philo_init(data);
}