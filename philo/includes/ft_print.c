/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:21:24 by clegros           #+#    #+#             */
/*   Updated: 2024/07/10 18:21:26 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	write_status(t_philo_status status, t_philo *philo)
{
	long	elapsed;

	elapsed = get_time(MILLISECOND) - philo->data->start_time;
	if (get_bool(&philo->philo_mutex, &philo->full))
		return ;
	if ((status == TAKE_FIRST_FORK || status == TAKE_SECOND_FORK)
		&& !simulation_end(philo->data))
		printf("%-6ld %d has taken a fork\n", elapsed, philo->id);
	else if (status == EATING && !simulation_end(philo->data))
		printf("%-6ld %d is eating\n", elapsed, philo->id);
	else if (status == SLEEPING && !simulation_end(philo->data))
		printf("%-6ld %d is sleeping\n", elapsed, philo->id);
	else if (status == THINKING && !simulation_end(philo->data))
		printf("%-6ld %d is thinking\n", elapsed, philo->id);
	else if (status == DIED)
		printf("%-6ld %d died\n", elapsed, philo->id);
	safe_mutex(&philo->data->m_print, UNLOCK);
}
