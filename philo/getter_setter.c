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

void	set_ulong(t_env *env, size_t *dest, size_t value)
{
	pthread_mutex_lock(&env->lock);
	*dest = value;
	pthread_mutex_unlock(&env->lock);
}

size_t	get_ulong(t_env *env, size_t *dest)
{
	size_t	res;

	pthread_mutex_lock(&env->lock);
	res = *dest;
	pthread_mutex_unlock(&env->lock);
	return (res);
}

void	set_long(t_env *env, long *dest, long value)
{
	pthread_mutex_lock(&env->lock);
	*dest = value;
	pthread_mutex_unlock(&env->lock);
}

long	get_long(t_env *env, long *dest)
{
	long	res;

	pthread_mutex_lock(&env->lock);
	res = *dest;
	pthread_mutex_unlock(&env->lock);
	return (res);
}
