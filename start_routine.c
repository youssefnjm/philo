/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 17:55:26 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/28 20:18:51 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_philo_die(t_philo *philo)
{
	size_t	time;
	size_t	last;

	time = get_current_time() - philo->env->start_routine;
	last = get_ulong(&philo->env->last_lock, &philo->last_meal);
	if (time - last > philo->env->time_to_die)
		return (1);
	return (0);
}

void	*monitor_routine(void *info)
{
	int		i;
	t_env	*env;

	env = (t_env *)info;
	wait_all(&env->philos[0]);
	while (!get_long(&env->dead_lock, &env->stop))
	{
		i = 0;
		while (i < env->philo_num
			&& !get_long(&env->dead_lock, &env->stop))
		{
			if (!get_long(&env->dead_lock, &env->philos[i].full)
				&& is_philo_die(&env->philos[i]))
			{
				set_long(&env->dead_lock, &env->stop, 1);
				print_died(&env->philos[i]);
				return (NULL);
			}
			i++;
		}
		usleep(500);
	}
	return (NULL);
}

int	start_simulation(t_env *env)
{
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
	usleep(100);
	env->start_routine = get_current_time();
	if (pthread_create(&env->monitor_thread, NULL
			, monitor_routine, env) != 0)
	{
		write(2, "error in create a thread\n", 26);
		return (1);
	}
	set_long(&env->lock, &env->wait_flag, 1);
	if (join_threads(env) == 1)
		return (1);
	return (0);
}
