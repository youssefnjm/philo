/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:55:26 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/16 22:28:27 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int is_philo_die(t_philo *philo);

void doing_event(t_philo *philo, size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
	{
		if (get_long(philo->env, &philo->env->stop) == 1)
		{
            return;
		}
	}
}

int is_philo_die(t_philo *philo)
{
	size_t time;

	if (get_long(philo->env, &philo->env->stop))
		return (1);
	time = get_current_time() - philo->env->start_routine;
	if (time - philo->last_meal >= philo->env->time_to_die)
	{
		if (philo->env->stop == 0)
		{
			set_long(philo->env, &philo->env->stop, 1);
			printf(RED"%ld %ld died\n"RESET, time, philo->philo_id);
			return (1);
		}
		return (1);
	}
	return (0);
}

int eat(t_philo *philo)
{
	size_t time;

	// take first fork
	pthread_mutex_lock(philo->first_f);
	time = get_current_time() - philo->env->start_routine;
	if (get_long(philo->env, &philo->env->stop))
	{
		pthread_mutex_unlock(philo->first_f);
		return (1);
	}
	printf("%ld %ld has taken a fork first\n", time, philo->philo_id);
	// take first second
	pthread_mutex_lock(philo->second_f);
	time = get_current_time() - philo->env->start_routine;
	if (get_long(philo->env, &philo->env->stop))
	{
		pthread_mutex_unlock(philo->first_f);
		pthread_mutex_unlock(philo->second_f);
		return (1);
	}
	printf("%ld %ld has taken a fork second\n", time, philo->philo_id);
	// eat
	time = get_current_time() - philo->env->start_routine;
	philo->last_meal = time;
	printf("%ld %ld is eating\n", time, philo->philo_id);
	doing_event(philo, philo->env->time_to_eat);
	if (get_long(philo->env, &philo->env->stop))
	{
		pthread_mutex_unlock(philo->first_f);
		pthread_mutex_unlock(philo->second_f);
		return (1);
	}
	// take off forks
	pthread_mutex_unlock(philo->first_f);
	pthread_mutex_unlock(philo->second_f);
	return (0);
}

void *philo_routine(void *info)
{
	t_philo *philo;
	size_t time;

	philo = (t_philo *)info;
	wait_all(philo);
	while (philo->env->meals_limit == -1 || philo->env->meals_limit > philo->eating_meals)
	{
		// think
		time = get_current_time() - philo->env->start_routine;
		printf("%ld %ld is thinking\n", time, philo->philo_id);
		if (get_long(philo->env, &philo->env->stop))
			break ;
		// eat
		if (eat(philo) == 1)
			break ;
		philo->eating_meals++;
		// sleep
		time = get_current_time() - philo->env->start_routine;
		printf("%ld %ld is sleeping\n", time, philo->philo_id);
		doing_event(philo, philo->env->time_to_sleep);
		if (get_long(philo->env, &philo->env->stop))
			break ;
	}
	return (NULL);
}

int monitor_routine(t_env *env)
{
	int i;

	while (1)
	{
		i = 0;
		while (i < env->philo_num)
		{
			if (is_philo_die(&env->philos[i]))
			{
				set_long(env, &env->stop, 1);
				return (1);
			}
			i++;
			// ft_usleep(100);
		}
	}
	return (0);
}

int start_simulation(t_env *env)
{
	int i;

	i = 0;
	if (env->philo_num == 1)
		return (0);
	else
	{
		if (create_threads(env, philo_routine) == 1)
			return (1);
		ft_usleep(100);
	}
	ft_usleep(100);
	env->start_routine = get_current_time();
	set_long(env, &env->wait_flag, 1);
	monitor_routine(env);
	if (join_threads(env) == 1)
		return (1);
	return (0);
}
