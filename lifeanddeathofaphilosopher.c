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
	ft_display_message(FORK, data);
	pthread_mutex_lock(data->philo.borrow);
	ft_display_message(FORK, data);
	ft_eat(data);
	pthread_mutex_unlock(data->philo.borrow);
	pthread_mutex_unlock(&data->philo.fork);
}

void	ft_eat(t_data *data)
{
	if (ft_new_meal(data) == 1)
	{
		ft_display_message(DEATH, data);
		pthread_mutex_lock(data->check_vitals);
		*data->end_simulation = 1;
		pthread_mutex_unlock(data->check_vitals);
		return ;
	}
	ft_display_message(EAT, data);
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
	ft_display_message(SLEEP, data);
	usleep(data->sleep * 1000);
}

void	ft_think(t_data *data)
{
	ft_display_message(THINK, data);
}
