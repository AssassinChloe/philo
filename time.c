/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:35:51 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/10 11:36:59 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_timer(t_time *time)
{
    long long sec;
    long long usec;
    int ms;

    gettimeofday(&time->current, NULL);
    sec = (time->current.tv_sec - time->start.tv_sec) * 1000;
    usec = (time->current.tv_usec - time->start.tv_usec) / 1000;
    ms = sec + usec;
	return (ms);
}

int ft_last_meal(t_data *data)
{
    struct timeval new_meal;
    long long sec;
    long long usec;
    int ms;

    gettimeofday(&new_meal, NULL);
    sec = (new_meal.tv_sec - data->philo.last_meal.tv_sec) * 1000;
    usec = (new_meal.tv_usec - data->philo.last_meal.tv_usec) / 1000;
    ms = sec + usec;
    data->philo.last_meal = new_meal;
    return(ms);
}
