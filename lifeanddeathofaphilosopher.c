/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifeanddeathofaphilosopher.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:59:15 by cassassi          #+#    #+#             */
/*   Updated: 2022/01/11 15:26:55 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_fork(t_data *data)
{
	pthread_mutex_lock(&data->philo.fork);
	ft_display_message(FORK, &data);
	pthread_mutex_lock(data->philo.borrow);
	ft_display_message(FORK, &data);
	ft_eat(data);
	pthread_mutex_unlock(&data->philo.fork);
	pthread_mutex_unlock(data->philo.borrow);
}

void	ft_eat(t_data *data)
{
	pthread_mutex_lock(&data->philo.meal_m);
	ft_last_meal(data);
	pthread_mutex_unlock(&data->philo.meal_m);
	ft_display_message(EAT, &data);
	if (data->philo.meal > 0)
	{
		pthread_mutex_lock(&data->philo.meal_m);
		data->philo.meal--;
		pthread_mutex_unlock(&data->philo.meal_m);
	}
	usleep((data->eat * 1000));
}

void	ft_sleep(t_data *data)
{
	ft_display_message(SLEEP, &data);
	usleep(data->sleep * 1000);
}

void	ft_think(t_data *data)
{
	ft_display_message(THINK, &data);
}

