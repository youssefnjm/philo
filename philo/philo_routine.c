/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 01:56:34 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/23 03:09:41 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	doing_event(t_philo *philo, size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		if (get_long(&philo->env->dead_lock, &philo->env->stop) == 1)
			return (1);
	}
	return (0);
}

int	eat(t_philo *philo)
{
	size_t last;

	pthread_mutex_lock(philo->first_f);
	if (get_long(&philo->env->dead_lock, &philo->env->stop))
	{
		pthread_mutex_unlock(philo->first_f);
		return (1);
	}
	// print_fork(philo);
	write_status(philo, " has taken a fork\n", 19);
	pthread_mutex_lock(philo->second_f);
	// print_fork(philo);
	write_status(philo, " has taken a fork\n", 19);
	last = get_current_time();
	set_ulong(&philo->env->last_lock, &philo->last_meal, last);
	// print_eating(philo);
	write_status(philo, " is eating\n", 12);
	if (doing_event(philo, philo->env->time_to_eat) == 1)
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
	philo->last_meal = get_current_time();
	if (philo->philo_id % 2 == 0)
		ft_usleep(50);
	while (!get_long(&philo->env->dead_lock, &philo->env->stop))
	{
		if (eat(philo) == 1)
			break ;
		philo->eating_meals++;
		if (philo->env->meals_limit != -1
			&& philo->env->meals_limit <= philo->eating_meals)
		{
			set_long(&philo->env->lock, &philo->full, 1);
			break ;
		}
		// print_sleep(philo);
		write_status(philo, " is sleeping\n", 14);
		doing_event(philo, philo->env->time_to_sleep);
		if (get_long(&philo->env->dead_lock, &philo->env->stop))
			break ;
		// print_think(philo);
		write_status(philo,  " is thinking\n", 14);
		
	}
	return (NULL);
}

void	*one_philo(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	wait_all(philo);
	philo->last_meal = get_current_time();
	print_think(philo);
	pthread_mutex_lock(philo->first_f);
	print_fork(philo);
	while (!get_long(&philo->env->dead_lock, &philo->env->stop))
		ft_usleep(10);
	return (NULL);
}
