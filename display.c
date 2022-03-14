/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:13:12 by cassassi          #+#    #+#             */
/*   Updated: 2022/01/11 16:09:18 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_display_message(int str, t_data *data)
{
	pthread_mutex_lock(data->display);
	pthread_mutex_lock(data->check_vitals);
	pthread_mutex_lock(&data->philo.meal_m);
	if (*data->end_simulation == 0 && data->philo.meal != 0)
	{
		pthread_mutex_unlock(&data->philo.meal_m);
		pthread_mutex_unlock(data->check_vitals);
		printf("%d %d", ft_timer(&data->time), data->philo.name);
		if (str == FORK)
			printf(" has taken a fork\n");
		else if (str == EAT)
			printf(" is eating\n");
		else if (str == SLEEP)
			printf(" is sleeping\n");
		else if (str == THINK)
			printf(" is thinking\n");
		else if (str == DEATH)
		{
			pthread_mutex_lock(data->check_vitals);
			data->philo.alive = 0;
			pthread_mutex_unlock(data->check_vitals);
			printf(" died\n");
		}
	}
	else
	{
		pthread_mutex_unlock(&data->philo.meal_m);
		pthread_mutex_unlock(data->check_vitals);
	}
	pthread_mutex_unlock(data->display);
}
