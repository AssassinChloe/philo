/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:13:12 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/29 17:44:47 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_display_death(t_data *data)
{
	*data->alive = -1;
	printf("%d %d", ft_timer(&data->time), data->philo.name);
	printf(" died\n");
}

void	ft_display_message(int str, t_data *data)
{
	pthread_mutex_lock(data->display);
	if (str == FORK && (*data->alive == 1 || *data->alive == -2))
	{
		printf("%d %d", ft_timer(&data->time), data->philo.name);
		printf(" has taken a fork\n");
	}
	else if (str == EAT && (*data->alive == 1 || *data->alive == -2))
	{
		printf("%d %d", ft_timer(&data->time), data->philo.name);
		printf(" is eating\n");
	}
	else if (str == SLEEP && (*data->alive == 1 || *data->alive == -2))
	{
		printf("%d %d", ft_timer(&data->time), data->philo.name);
		printf(" is sleeping\n");
	}
	else if (str == THINK && (*data->alive == 1 || *data->alive == -2))
	{
		printf("%d %d", ft_timer(&data->time), data->philo.name);
		printf(" is thinking\n");
	}
	else if (str == DEATH && *data->alive == 1)
		ft_display_death(data);
	pthread_mutex_unlock(data->display);
}
