#include "philo.h"

void	ft_sleep(t_data *data, time_t end)
{
	time_t	wake_up;

	wake_up = get_time(data) + end;
	while (data->dead != 1)
	{
		if (get_time(data) >= wake_up)
			break ;
		usleep(2 * data->nb_philo);
	}
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	int	j;

	i = 0;
	if (s1[i] || s2[i])
	{
		i++;
		j = s1[i] - s2[i];
		if (j != 0)
			return (1);
	}
	return (0);
}

time_t	get_time(t_data *data)
{
	static struct timeval	time;

	gettimeofday(&time, NULL);
	return (((time.tv_sec * 1000) + (time.tv_usec / 1000)) - data->start_time);
}