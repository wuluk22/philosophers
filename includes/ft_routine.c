#include "philo.h"

void	*eat(void *philo_pointer)
{
	t_philo	*philo;

	philo = (t_philo *)philo_pointer;
	pthread_mutex_lock(&philo->data->forks[philo->left_fork]);
	pthread_mutex_lock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_lock(&philo->data->m_print);
	// --- stuff ---
	printf("Philosopher %d is eating\n", philo->id);
	// --- stuff ---
	pthread_mutex_unlock(&philo->data->m_print);
	pthread_mutex_unlock(&philo->data->forks[philo->right_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->left_fork]);
	return (NULL);
}

void	*routine(void *data_pointer)
{
	// --- eat, sleep, repeat ---
	t_philo	*philo;

	philo = (t_philo *)data_pointer;
	while (1)
	{
		eat(philo);
		printf("Philosopher %d is sleeping\n", philo->id);
		usleep(philo->data->t_to_sleep * 1000);
		printf("Philosopher %d is thinking\n", philo->id);
	}
	return (NULL);
}


