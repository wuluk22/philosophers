/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:20:07 by clegros           #+#    #+#             */
/*   Updated: 2024/07/10 18:20:09 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = -1;
	while (++i < data->nbr_philo)
	{
		philo = data->philo + i;
		safe_mutex(&philo->philo_mutex, DESTROY);
	}
	safe_mutex(&data->m_print, DESTROY);
	safe_mutex(&data->data_mutex, DESTROY);
	free(data->forks);
	free(data->philo);
}
