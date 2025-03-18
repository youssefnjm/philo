/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:55:26 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/18 02:15:41 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_die(t_philo *philo)
{
	size_t	time;

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

int	monitor_routine(t_env *env)
{
	int	i;

	while (!get_long(env, &env->stop) && env->philos_full != env->philo_num)
	{
		i = 0;
		while (i < env->philo_num)
		{	
			if (get_long(env, &env->philos[i].full))
				env->philos_full = env->philos_full + 1;
			if (!get_long(env, &env->philos[i].full)
				&& is_philo_die(&env->philos[i]))
			{
				set_long(env, &env->stop, 1);
				return (1);
			}
			i++;
			// puts("gggg");
		}
		ft_usleep(10);
	}
	return (0);
}

int	start_simulation(t_env *env)
{
	if (env->philo_num == 1)
		return (0);
	else
	{
		if (create_threads(env, philo_routine) == 1)
			return (1);
	}
	ft_usleep(100);
	env->start_routine = get_current_time();
	set_long(env, &env->wait_flag, 1);
	monitor_routine(env);
	if (join_threads(env) == 1)
		return (1);
	return (0);
}
