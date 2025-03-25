/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getter_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 16:46:56 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/18 01:49:07 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_ulong(pthread_mutex_t *lock, size_t *dest, size_t value)
{
	pthread_mutex_lock(lock);
	*dest = value;
	pthread_mutex_unlock(lock);
}

size_t	get_ulong(pthread_mutex_t *lock, size_t *dest)
{
	size_t	res;

	pthread_mutex_lock(lock);
	res = *dest;
	pthread_mutex_unlock(lock);
	return (res);
}

void	set_long(pthread_mutex_t *lock, long *dest, long value)
{
	pthread_mutex_lock(lock);
	*dest = value;
	pthread_mutex_unlock(lock);
}

long	get_long(pthread_mutex_t *lock, long *dest)
{
	long	res;

	pthread_mutex_lock(lock);
	res = *dest;
	pthread_mutex_unlock(lock);
	return (res);
}
