/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:13:12 by cassassi          #+#    #+#             */
/*   Updated: 2022/01/07 15:33:59 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_display_message(int str, t_data *data)
{
	pthread_mutex_lock(data->display);
	if (*data->alive == 1 && data->philo.meal != 0)
	{
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
			*data->alive = -1;
			printf(" died\n");
		}
	}
	pthread_mutex_unlock(data->display);
}
