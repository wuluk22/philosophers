/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sync_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:21:43 by clegros           #+#    #+#             */
/*   Updated: 2024/07/10 18:21:44 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increase_long(t_mtx *mutex, long *value)
{
	safe_mutex(mutex, LOCK);
	(*value)++;
	safe_mutex(mutex, UNLOCK);
}

void	wait_all_threads(t_data *data)
{
	while (!get_bool(&data->data_mutex, &data->all_threads_ready))
		;
}

void	fairly_synchronize_philos(t_philo *philo)
{
	if (philo->data->nbr_philo % 2 == 0)
	{
		if (philo->id % 2 == 0)
			precise_usleep(3e4, philo->data);
	}
	else
		if (philo->id % 2)
			thinking(philo, true);
}

bool	all_threads_running(t_mtx *mutex, long *threads,
		long philo_nbr)
{
	bool	ret;

	ret = false;
	safe_mutex(mutex, LOCK);
	if (*threads == philo_nbr)
		ret = true;
	safe_mutex(mutex, UNLOCK);
	return (ret);
}
