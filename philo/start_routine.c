/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:55:26 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/23 01:15:04 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_die(t_philo *philo)
{
	size_t	time;
	size_t	last;

	if (get_long(&philo->env->dead_lock, &philo->env->stop))
		return (1);
	time = get_current_time();
	last = get_ulong(&philo->env->last_lock, &philo->last_meal);
	if (time - last > philo->env->time_to_die)
	{
		if (philo->env->stop == 0)
		{
			set_long(&philo->env->dead_lock, &philo->env->stop, 1);
			print_died(philo);
			return (1);
		}
		return (1);
	}
	return (0);
}

int	monitor_routine(t_env *env)
{
	int	i;

	ft_usleep(50);
	while (!get_long(&env->dead_lock, &env->stop)
		&& env->philos_full != env->philo_num)
	{
		i = 0;
		while (i < env->philo_num)
		{
			if (get_long(&env->dead_lock, &env->philos[i].full))
			{
				env->philos_full = env->philos_full + 1;
				return (1);
			}
			if (!get_long(&env->dead_lock, &env->philos[i].full)
				&& is_philo_die(&env->philos[i]))
			{
				set_long(&env->dead_lock, &env->stop, 1);
				return (1);
			}
			i++;
		}
		ft_usleep(5);
	}
	return (0);
}

int	start_simulation(t_env *env)
{
	int	i;

	i = 0;
	if (env->philo_num == 1)
	{
		if (create_threads(env, one_philo) == 1)
			return (1);
	}
	else
	{
		if (create_threads(env, philo_routine) == 1)
			return (1);
	}
	ft_usleep(100);
	env->start_routine = get_current_time();
	set_long(&env->lock, &env->wait_flag, 1);
	monitor_routine(env);
	if (join_threads(env) == 1)
		return (1);
	return (0);
}
