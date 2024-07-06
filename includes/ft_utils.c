#include "philo.h"



static int	is_digit(char **av)
{
	int	i;
	int	j;

	i = -1;
	while (av[++i])
	{
		j = -1;
		while (av[i][++j])
			if (av[i][j] < 48 || av[i][j] > 57)
				return (1);
	}
	return (0);
}

long long	ft_atol(char *av)
{
	int			sign;
	long long	nbr;

	sign = 0;
	nbr = 0;
	while ((*av >= 9 && *av <= 13) || *av == 32)
		av++;
	if (*av == 45 || *av == 43)
	{
		if (*av == 45)
			sign++;
		av++;
	}
	while (*av >= 48 && *av <= 57)
	{
		nbr = (nbr * 10) + (*av - 48);
		av++;
	}
	if ((sign % 2) > 0)
		nbr = -nbr;
	return (nbr);
}

int	check_value(char **av)
{
	int	i;

	i = -1;
	if (is_digit(av))
		return (1);
	while (av[++i])
		if (ft_atol(av[i]) > INT_MAX || !ft_atol(av[i]) || ft_atol(av[i]) < 0)
			return (1);
	return (0);
}