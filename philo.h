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

typedef struct s_data
{
    struct timeval  start;
	struct timeval  current;
}   t_data;

typedef struct s_philo
{
    pthread_mutex_t fork;
    int name;
	int die;
    int eat;
    int sleep;
    int meal;
    t_data time;
}	t_philo;


int ft_atoi(const char *str);
int ft_timer(t_data *data);

#endif
