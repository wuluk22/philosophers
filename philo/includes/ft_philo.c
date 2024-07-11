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
