/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 01:56:34 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/28 17:44:47 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ssleep(t_philo *philo)
{
	write_status(philo, " is sleeping\n", 14);
	doing_event(philo, philo->env->time_to_sleep);
}

void	take_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->first_f);
	write_status(philo, " has taken a fork\n", 19);
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
	write_status(philo, " has taken a fork\n", 19);
}

void	eat(t_philo *philo)
{
	size_t last;
	
	write_status(philo, " is eating\n", 12);
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
		write_status(philo, " is thinking\n", 14);
	}
	return (NULL);
}

void	*one_philo(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	wait_all(philo);
	philo->last_meal = get_current_time();
	write_status(philo, " is thinking\n", 14);
	pthread_mutex_lock(philo->first_f);
	write_status(philo, " has taken a fork\n", 19);
	while (!get_long(&philo->env->dead_lock, &philo->env->stop))
		usleep(philo->env->time_to_die / 10);
	return (NULL);
}
