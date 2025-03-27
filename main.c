/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:56:51 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/17 23:22:17 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_env			env;
	t_philo			philo[200];
	pthread_mutex_t	forks[200];

	env.philos = philo;
	env.forks = forks;
	if (handle_inputs(&env, ac, av) == 1)
		return (1);
	if (start_simulation(&env) == 1)
		return (1);
	clean_all(&env);
	return (0);
}
