/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 15:23:15 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/12 16:21:05 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atoi(const char *str)
{
	int		i;
	int		signe;
	size_t	result;

	i = 0;
	signe = 1;
	result = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = (-1);
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i++] - 48);
	}
	return (result * signe);
}

static	int	check_overflow(const char *str)
{
	int		i;
	size_t	n;

	i = 0;
	n = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - 48);
		if (n > 9223372036854775807)
			return (1);
		i++;
	}
	return (0);
}

static	int	check_range(int pos, char *str)
{
	size_t	num;

	if (check_overflow(str) == 1)
		return (1);
	num = ft_atoi(str);
	if (num == 0)
		return (1);
	if (pos == 1 && num > 200)
		return (1);
	if (pos != 1 && pos != 5 && num < 60)
		return (1);
	return (0);
}

static	int	contains_non_digit(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		return (1);
	if (str[i] == '+')
		i++;
	while (str[i])
	{
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

int	handle_inputs(t_env *env, int ac, char **av)
{
	int	i;

	i = 1;
	if (!(ac == 5 || ac == 6))
		return (write(2, "unvalid argement numbers\n", 26), 1);
	while (i < ac)
	{
		if (contains_non_digit(av[i]) == 1)
			return (write(2, "unvalid inputs\n", 16), 1);
		if (check_range(i, av[i]) == 1)
			return (write(2, "unvalid inputs\n", 16), 1);
		i++;
	}
	i = 0;
	if (init_env(env, ac, av) == 1)
		return (1);
	return (0);
}
