/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 18:08:44 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/27 17:47:42 by ynoujoum         ###   ########.fr       */
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

void	print_died(t_philo *philo)
{
	size_t	time;

	pthread_mutex_lock(&philo->env->write_lock);
	time = get_current_time() - philo->env->start_routine;
	ft_putnbr(time);
	write(1, " ", 1);
	ft_putnbr(philo->philo_id);
	write(1, " died\n", 7);
	pthread_mutex_unlock(&philo->env->write_lock);
}

void	write_status(t_philo *philo, char *str, int len)
{
	size_t	time;

	pthread_mutex_lock(&philo->env->write_lock);
	if (get_long(&philo->env->dead_lock, &philo->env->stop) == 0)
	{
		time = get_current_time() - philo->env->start_routine;
		ft_putnbr(time);
		write(1, " ", 1);
		ft_putnbr(philo->philo_id);
		write(1, str, len);
		write(1, "\n", 1);
	}
	pthread_mutex_unlock(&philo->env->write_lock);
}
