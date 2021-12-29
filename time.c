/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:35:51 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/28 20:31:53 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_timer(t_time *time)
{
	gettimeofday(&time->current, NULL);
	return ((int)((time->current.tv_sec - time->start.tv_sec) * 1000)
			+ ((time->current.tv_usec - time->start.tv_usec) / 1000));
}

void	ft_last_meal(t_data *data)
{
	gettimeofday(&data->new_meal, NULL);
	if ((((data->new_meal.tv_sec - data->philo.last_meal->tv_sec) * 1000)
			+ ((data->new_meal.tv_usec - data->philo.last_meal->tv_usec)
				/ 1000)) > data->die)
		ft_die(data);
	*data->philo.last_meal = data->new_meal;
}

void	ft_check_last_meal(t_data *data)
{
	gettimeofday(&data->new_meal, NULL);
	if ((((data->new_meal.tv_sec - data->philo.last_meal->tv_sec) * 1000)
			+ ((data->new_meal.tv_usec - data->philo.last_meal->tv_usec)
				/ 1000)) > data->die)
		ft_die(data);
}
