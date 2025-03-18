/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:55:26 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/18 01:09:13 by ynoujoum         ###   ########.fr       */
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
            return;
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

	if (get_long(philo->env, &philo->env->stop))
		return (1);
	// take first fork
	pthread_mutex_lock(philo->first_f);
	time = get_current_time() - philo->env->start_routine;
	if (get_long(philo->env, &philo->env->stop))
	{
		pthread_mutex_unlock(philo->first_f);
		return (1);
	}
	print_fork(philo, time);
	// take first second
	pthread_mutex_lock(philo->second_f);
	time = get_current_time() - philo->env->start_routine;
	if (get_long(philo->env, &philo->env->stop))
	{
		pthread_mutex_unlock(philo->first_f);
		pthread_mutex_unlock(philo->second_f);
		return (1);
	}
	print_fork(philo, time);
	// eat
	time = get_current_time() - philo->env->start_routine;
	philo->last_meal = time;
	print_eating(philo, time);
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
	while (1)
	{
		// think
		time = get_current_time() - philo->env->start_routine;
		print_think(philo, time);
		if (get_long(philo->env, &philo->env->stop))
			break ;
		// eat
		if (eat(philo) == 1)
			break ;
		philo->eating_meals++;
		if (philo->env->meals_limit != -1 && philo->env->meals_limit <= philo->eating_meals)
		{
			set_long(philo->env, &philo->full, 1);
			break ;
		}
		// sleep
		time = get_current_time() - philo->env->start_routine;
		print_sleep(philo, time);
		doing_event(philo, philo->env->time_to_sleep);
		if (get_long(philo->env, &philo->env->stop))
			break ;
	}
	return (NULL);
}

int monitor_routine(t_env *env)
{
	int i;

	while (!get_long(env, &env->stop) && env->philos_full != env->philo_num)
	{
		i = 0;
		while (i < env->philo_num)
		{	
			if (get_long(env, &env->philos[i].full))
				env->philos_full = env->philos_full + 1;
			if (!get_long(env, &env->philos[i].full) && is_philo_die(&env->philos[i]))
			{
				set_long(env, &env->stop, 1);
				return (1);
			}
			i++;
		}
		ft_usleep(100);
	}
	return (0);
}

int start_simulation(t_env *env)
{
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
