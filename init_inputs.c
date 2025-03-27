/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 16:27:11 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/23 01:11:23 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->philo_num)
	{
		env->philos[i].philo_id = i + 1;
		env->philos[i].dead = 0;
		env->philos[i].eating_meals = 0;
		env->philos[i].last_meal = 0;
		if (i == (env->philo_num - 1))
		{
			env->philos[i].first_f = &env->forks[(i + 1) % env->philo_num];
			env->philos[i].second_f = &env->forks[i];
		}
		else
		{
			env->philos[i].first_f = &env->forks[i];
			env->philos[i].second_f = &env->forks[(i + 1) % env->philo_num];
		}
		env->philos[i].env = env;
		env->philos[i].full = 0;
		i++;
	}
}

int	init_forks(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->philo_num)
	{
		if (pthread_mutex_init(&env->forks[i], NULL) != 0)
		{
			while (--i >= 0)
				pthread_mutex_destroy(&env->forks[i]);
			pthread_mutex_destroy(&env->lock);
			return (write(2, "error in mutex\n", 16), 1);
		}
		i++;
	}
	return (0);
}

int	init_mutex(t_env *env)
{
	if (pthread_mutex_init(&env->write_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&env->dead_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&env->write_lock);
		pthread_mutex_destroy(&env->write_lock);
		return (1);
	}
	if (pthread_mutex_init(&env->last_lock, NULL) != 0)
	{
		pthread_mutex_destroy(&env->write_lock);
		pthread_mutex_destroy(&env->dead_lock);
		return (1);
	}
	if (pthread_mutex_init(&env->lock, NULL) != 0)
	{
		pthread_mutex_destroy(&env->write_lock);
		pthread_mutex_destroy(&env->dead_lock);
		pthread_mutex_destroy(&env->last_lock);
		return (1);
	}
	return (0);
}

int	init_env(t_env *env, int ac, char **av)
{
	env->stop = 0;
	env->philo_num = ft_atoi(av[1]);
	env->time_to_die = ft_atoi(av[2]);
	env->time_to_eat = ft_atoi(av[3]);
	env->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		env->meals_limit = ft_atoi(av[5]);
	else
		env->meals_limit = -1;
	env->start_routine = 0;
	env->philos_full = 0;
	if (init_mutex(env) == 1)
		return (1);
	if (init_forks(env) == 1)
		return (1);
	init_philos(env);
	return (0);
}

void	clean_all(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->philo_num)
		pthread_mutex_destroy(&env->forks[i++]);
	pthread_mutex_destroy(&env->write_lock);
	pthread_mutex_destroy(&env->dead_lock);
	pthread_mutex_destroy(&env->last_lock);
	pthread_mutex_destroy(&env->lock);
}
