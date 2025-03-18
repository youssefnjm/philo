/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:08:44 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/18 01:48:00 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putnbr(size_t n)
{
	char	c;

	if (n > 9)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	else
	{
		c = n + 48;
		write(1, &c, 1);
	}
}

void	print_fork(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->env->lock);
	time = get_current_time() - philo->env->start_routine;
	ft_putnbr(time);
	write(1, " ", 1);
	ft_putnbr(philo->philo_id);
	write(1, " has taken a fork\n", 19);
	pthread_mutex_unlock(&philo->env->lock);
}

void	print_eating(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->env->lock);
	time = get_current_time() - philo->env->start_routine;
	ft_putnbr(time);
	write(1, " ", 1);
	ft_putnbr(philo->philo_id);
	write(1, " is eating\n", 12);
	pthread_mutex_unlock(&philo->env->lock);
}

void	print_sleep(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->env->lock);
	time = get_current_time() - philo->env->start_routine;
	ft_putnbr(time);
	write(1, " ", 1);
	ft_putnbr(philo->philo_id);
	write(1, " is sleeping\n", 14);
	pthread_mutex_unlock(&philo->env->lock);
}

void	print_think(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->env->lock);
	time = get_current_time() - philo->env->start_routine;
	ft_putnbr(time);
	write(1, " ", 1);
	ft_putnbr(philo->philo_id);
	write(1, " is thinking\n", 14);
	pthread_mutex_unlock(&philo->env->lock);
}
