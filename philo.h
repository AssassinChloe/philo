/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:44:38 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/08 15:51:01 by cassassi         ###   ########.fr       */
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
    struct timeval  start;
	struct timeval  current;
}   t_time;

typedef struct s_philo
{
    pthread_mutex_t fork;
    pthread_mutex_t borrow;
    int name;
	int deadoralive;
    int meal;
    struct timeval last_meal;
}	t_philo;

typedef struct s_data
{
    t_time time;
    t_philo philo;
    int philo_nb;
    int sleep;
    int eat;
    int die;
}   t_data;

int ft_error(char *err);
int ft_atoi(const char *str);
int ft_timer(t_time *time);
void ft_fork(t_data *data);
void ft_eat(t_data *data);
void ft_sleep(t_data *data);
void ft_think(t_data *data);
void    ft_display_message(int str, t_data *data);
#endif
