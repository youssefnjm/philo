/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 01:56:34 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/18 02:44:17 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	doing_event(t_philo *philo, size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		if (get_long(philo->env, &philo->env->stop) == 1)
			return ;
	}
}

int	eat(t_philo *philo)
{
	if (get_long(philo->env, &philo->env->stop))
		return (1);
	pthread_mutex_lock(philo->first_f);
	if (get_long(philo->env, &philo->env->stop))
	{
		pthread_mutex_unlock(philo->first_f);
		return (1);
	}
	print_fork(philo);
	pthread_mutex_lock(philo->second_f);
	if (get_long(philo->env, &philo->env->stop))
	{
		pthread_mutex_unlock(philo->first_f);
		pthread_mutex_unlock(philo->second_f);
		return (1);
	}
	print_fork(philo);
	philo->last_meal = get_current_time() - philo->env->start_routine;
	print_eating(philo);
	doing_event(philo, philo->env->time_to_eat);
	if (get_long(philo->env, &philo->env->stop))
	{
		pthread_mutex_unlock(philo->first_f);
		pthread_mutex_unlock(philo->second_f);
		return (1);
	}
	pthread_mutex_unlock(philo->first_f);
	pthread_mutex_unlock(philo->second_f);
	return (0);
}

void	*philo_routine(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	wait_all(philo);
	while (1)
	{
		print_think(philo);
		if (get_long(philo->env, &philo->env->stop))
			break ;
		if (eat(philo) == 1)
			break ;
		philo->eating_meals++;
		if (philo->env->meals_limit != -1
			&& philo->env->meals_limit <= philo->eating_meals)
		{
			set_long(philo->env, &philo->full, 1);
			break ;
		}
		print_sleep(philo);
		doing_event(philo, philo->env->time_to_sleep);
		if (get_long(philo->env, &philo->env->stop))
			break ;
	}
	return (NULL);
}

void	*one_philo(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	wait_all(philo);
	print_think(philo);
	pthread_mutex_lock(philo->first_f);
	print_fork(philo);
	while (!get_long(philo->env, &philo->env->stop))
		ft_usleep(10);
	return (NULL);
}
