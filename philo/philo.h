/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynoujoum <ynoujoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:57:21 by ynoujoum          #+#    #+#             */
/*   Updated: 2025/03/28 20:21:25 by ynoujoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_env	t_env;

typedef struct s_philo
{
	pthread_t		thread;
	long			philo_id;
	long			dead;
	long			eating_meals;
	long			full;
	size_t			last_meal;
	pthread_mutex_t	*second_f;
	pthread_mutex_t	*first_f;
	t_env			*env;
}	t_philo;

typedef struct s_env
{
	pthread_t		monitor_thread;
	long			stop;
	long			wait_flag;
	long			philo_num;
	long			meals_limit;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
	size_t			start_routine;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	last_lock;
	pthread_mutex_t	lock;
	pthread_mutex_t	*forks;
	t_philo			*philos;
}	t_env;

int		handle_inputs(t_env *env, int ac, char **av);
long	ft_atoi(const char *str);
int		init_env(t_env *env, int ac, char **av);
void	clean_all(t_env *env);
int		start_simulation(t_env *env);

size_t	get_current_time(void);
int		doing_event(t_philo *philo, size_t milliseconds);
void	wait_all(t_philo *philo);
int		create_threads(t_env *env, void *fn());
int		join_threads(t_env *env);

void	set_ulong(pthread_mutex_t *lock, size_t *dest, size_t value);
void	set_long(pthread_mutex_t *lock, long *dest, long value);
size_t	get_ulong(pthread_mutex_t *lock, size_t *dest);
long	get_long(pthread_mutex_t *lock, long *dest);

void	print_died(t_philo *philo);
void	write_status(t_philo *philo, char *str, int len);

void	*philo_routine(void *info);
void	*one_philo(void *info);

#endif