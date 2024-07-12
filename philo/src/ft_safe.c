/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_safe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clegros <clegros@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:21:33 by clegros           #+#    #+#             */
/*   Updated: 2024/07/10 18:22:36 by clegros          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc(bytes);
	if (ret == NULL)
		error_exit("Malloc error");
	return (ret);
}

static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EAGAIN)
		error_exit("Not enought ressources");
	else if (status == EPERM)
		error_exit("Not appropriate ressources");
	else if (status == EINVAL && opcode == CREATE)
		error_exit("attr value is invalid");
	else if (status == EINVAL && (opcode == JOIN || opcode == DETACH))
		error_exit("value not joinable");
	else if (status == ESRCH)
		error_exit("no thread corresponding were found");
	else if (status == EDEADLK)
		error_exit("deadlock");
}

void	safe_thread(pthread_t *thread, void *(*foo)(void *), void *data,
			t_opcode opcode)
{
	if (opcode == CREATE)
		handle_thread_error(pthread_create(thread, NULL, foo, data), opcode);
	else if (opcode == JOIN)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (opcode == DETACH)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("wrong opcode");
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK
			|| opcode == DESTROY))
		error_exit("mutex value is invalid");
	else if (status == EINVAL && opcode == INIT)
		error_exit("attr value is invalid");
	else if (status == EDEADLK)
		error_exit("deadlock would occur");
	else if (status == EPERM)
		error_exit("the current thread doesn't hold a lock on mutex");
	else if (status == ENOMEM)
		error_exit("cannot allocate enough memory");
	else if (status == EBUSY)
		error_exit("mutex is locked");
}

void	safe_mutex(t_mtx *mutex, t_opcode opcode)
{
	if (opcode == LOCK)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if (opcode == INIT)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else
		printf("wrong opcode for mutex handle\n");
}
