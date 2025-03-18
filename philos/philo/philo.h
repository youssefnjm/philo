/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:57:21 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/18 01:04:15 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

#define RED "\033[1;31m"
#define RESET "\033[0m"
#define GREEN "\033[1;32m"

typedef struct s_env t_env;

typedef struct s_philo
{
	pthread_t		thread;
	long			philo_id;
	long			dead;
	long			eating_meals;
	size_t			last_meal;
	long			full; //
	pthread_mutex_t	*second_f;
	pthread_mutex_t	*first_f;
	t_env			*env;
}	t_philo;

typedef struct s_env
{
	long			stop;
	long			wait_flag;
	long			philo_num;
	long			philos_full; //
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	long			meals_limit;
	size_t			start_routine;
	size_t			end_routine;
	pthread_mutex_t	lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_env;

int		handle_inputs(t_env *env, int ac, char **av);
long	ft_atoi(const char *str);
int		init_env(t_env *env, int ac, char **av);
int		start_simulation(t_env *env);

// utils
size_t	get_current_time();
void	ft_usleep(size_t milliseconds);
void	wait_all(t_philo *philo);
int 	create_threads(t_env *env, void *fn());
int 	join_threads(t_env *env);

// setter and getter
void set_ulong(t_env *env, size_t *dest, size_t value);
void set_long(t_env *env, long *dest, long value);
size_t get_ulong(t_env *env, size_t *dest);
long get_long(t_env *env, long *dest);

// print
void	print_fork(t_philo *philo, size_t time);
void	print_eating(t_philo *philo, size_t time);
void	print_sleep(t_philo *philo, size_t time);
void	print_think(t_philo *philo, size_t time);

#endif