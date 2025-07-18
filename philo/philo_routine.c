/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 01:56:34 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/28 20:17:55 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ssleep(t_philo *philo)
{
	write_status(philo, " is sleeping", 12);
	doing_event(philo, philo->env->time_to_sleep);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->first_f);
	write_status(philo, " has taken a fork", 17);
	if (get_long(&philo->env->dead_lock, &philo->env->stop))
	{
		pthread_mutex_unlock(philo->first_f);
		return ;
	}
	pthread_mutex_lock(philo->second_f);
	if (get_long(&philo->env->dead_lock, &philo->env->stop))
	{
		pthread_mutex_unlock(philo->first_f);
		pthread_mutex_unlock(philo->second_f);
		return ;
	}
	write_status(philo, " has taken a fork", 17);
}

void	eat(t_philo *philo)
{
	size_t	last;

	write_status(philo, " is eating", 10);
	last = get_current_time() - philo->env->start_routine;
	set_ulong(&philo->env->last_lock, &philo->last_meal, last);
	doing_event(philo, philo->env->time_to_eat);
	philo->eating_meals++;
	pthread_mutex_unlock(philo->first_f);
	pthread_mutex_unlock(philo->second_f);
}

void	*philo_routine(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	wait_all(philo);
	if (philo->philo_id % 2)
		usleep(1000);
	while (!philo->env->stop)
	{
		take_forks(philo);
		eat(philo);
		if (philo->env->meals_limit != -1
			&& philo->env->meals_limit <= philo->eating_meals)
		{
			set_long(&philo->env->lock, &philo->full, 1);
			break ;
		}
		ssleep(philo);
		write_status(philo, " is thinking", 12);
	}
	return (NULL);
}

void	*one_philo(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	wait_all(philo);
	philo->last_meal = 0;
	write_status(philo, " is thinking", 12);
	pthread_mutex_lock(philo->first_f);
	write_status(philo, " has taken a fork", 17);
	while (!get_long(&philo->env->dead_lock, &philo->env->stop))
		usleep(philo->env->time_to_die / 10);
	return (NULL);
}
