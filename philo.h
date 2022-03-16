/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:44:38 by cassassi          #+#    #+#             */
/*   Updated: 2022/01/11 15:31:42 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <stdio.h>
# include <sys/time.h>

# define EAT 22
# define SLEEP 23
# define FORK 24
# define THINK 25
# define DEATH 26

typedef struct s_time
{
	struct timeval	start;
	struct timeval	current;
}	t_time;

typedef struct s_philo
{
	pthread_mutex_t	fork;
	pthread_mutex_t	meal_m;
	pthread_mutex_t	*borrow;
	int				name;
	int				meal;
	struct timeval	*last_meal;
}	t_philo;

typedef struct s_data
{
	t_time			time;
	t_philo			philo;
	int				*end_simulation;
	int				philo_nb;
	int				sleep;
	int				eat;
	int				die;
	struct timeval	new_meal;
	pthread_mutex_t	*display;
	pthread_mutex_t	*check_vitals;
}	t_data;

typedef struct s_init
{
	struct timeval	init_time;
	int				philosophers;
	int				*dead;
	pthread_mutex_t	*display;
	pthread_t		*th;
	pthread_mutex_t	*check_vitals;
}	t_init;

int		ft_error(char *err);
int		ft_atoi(const char *str);
int		ft_timer(t_time *time);
void	ft_fork(t_data *data);
void	ft_eat(t_data *data);
void	ft_sleep(t_data *data);
void	ft_think(t_data *data);
void	ft_display_message(int str, t_data *data);
int		ft_new_meal(t_data *data);
int		ft_init_data(t_data **data, t_init *var, char **argv, int argc);
int		ft_init_data_2(t_data **data, t_init *var, int i);
int		ft_init_var(t_init *var, char **argv);
void	ft_init_forks(t_data **data, t_init *var);
void	ft_init_philo(t_data **data, t_init *var);
void	*the_matrix(void *arg);
void	ft_ending(t_init *var, t_data **data);
int		ft_free(t_data **data, t_init *var);
int		ft_check_last_meal(t_data *data);
void	ft_check_vitals(t_data **data, int philosophers);

#endif
