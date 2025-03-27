/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 18:18:41 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/27 18:30:06 by ynoujoum         ###   ########.fr       */
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
		usleep(100);
	}
	return (0);
}

size_t	get_current_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	wait_all(t_philo *philo)
{
	long	check;

	while (1)
	{
		check = get_long(&philo->env->lock, &philo->env->wait_flag);
		if (check == 1)
			break ;
	}
}

int	create_threads(t_env *env, void *fn())
{
	int	i;

	i = 0;
	while (i < env->philo_num)
	{
		if (pthread_create(&env->philos[i].thread, NULL
				, fn, &env->philos[i]) != 0)
		{
			write(2, "error in create a thread\n", 26);
			return (1);
		}
		i++;
	}
	return (0);
}

int	join_threads(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->philo_num)
	{
		if (pthread_join(env->philos[i].thread, NULL) != 0)
		{
			write(2, "error in create a thread\n", 26);
			return (1);
		}
		i++;
	}
	return (0);
}
