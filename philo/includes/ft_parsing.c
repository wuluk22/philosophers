/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:20:53 by clegros           #+#    #+#             */
/*   Updated: 2024/07/10 18:20:55 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}

static inline bool	is_digit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*valid_input(const char *str)
{
	int			len;
	const char	*number;

	len = 0;
	while (is_space(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("Only positive values are possible.");
	if (!is_digit(*str))
		error_exit("The input is not a correct digit");
	number = str;
	while (is_digit(*str++))
		++len;
	if (len > 10)
		error_exit("INT_MAX is the limit.");
	return (number);
}

long	ft_atol(const char *str)
{
	long	number;

	number = 0;
	str = valid_input(str);
	while (is_digit(*str))
		number = (number * 10) + (*str++ - '0');
	if (number > INT_MAX)
		error_exit("INT_MAX is the limit.");
	return (number);
}

void	parse_input(t_data *data, char **av)
{
	data->nbr_philo = ft_atol(av[1]);
	if (data->nbr_philo > PHILO_MAX)
	{
		printf("%d is the max of philos\n", PHILO_MAX);
		exit(EXIT_FAILURE);
	}
	data->t_to_die = ft_atol(av[2]) * 1e3;
	data->t_to_eat = ft_atol(av[3]) * 1e3;
	data->t_to_sleep = ft_atol(av[4]) * 1e3;
	if (data->t_to_die < 6e4
		|| data->t_to_eat < 6e4
		|| data->t_to_sleep < 6e4)
		error_exit("Use timestamps major than 60ms\n");
	if (av[5])
		data->lmt_number_meals = ft_atol(av[5]);
	else
		data->lmt_number_meals = -1;
}
