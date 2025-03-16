/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:56:51 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/15 18:14:54 by ynoujoum         ###   ########.fr       */
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
	return (0);
}


// printf("env :dead[%d] philo_num[%d] time_to_die[%ld] time_to_eat[%ld]\
// 	time_to_sleep[%ld] meals_limit[%ld] start_routine[%zu] end_routine[%zu]\n"
// 	, env.dead, env.philo_num, env.time_to_die, env.time_to_eat, env.time_to_sleep,
// 	 env.meals_limit, env.start_routine, env.end_routine);
// int i = 0;
// while (i < env.philo_num)
// {
// 	puts("--------------------");
// 	printf("philo id :%d\n", env.philos[i].philo_id);
// 	printf("philo dead :%d\n", *env.philos[i].dead);
// 	printf("philo eating_meals :%zu\n", env.philos[i].eating_meals);
// 	printf("philo last_meal :%zu\n", env.philos[i].last_meal);
// 	printf("philo first_f :%p\n", env.philos[i].first_f);
// 	printf("philo second_f :%p\n", env.philos[i].second_f);
// 	i++;
// }