/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:13:12 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/28 20:46:40 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_display_time_name(t_data *data)
{
	ft_putnbr(ft_timer(&data->time));
	ft_putchar(' ');
	ft_putnbr(data->philo.name);

}
void	ft_display_message(int str, t_data *data)
{
	pthread_mutex_lock(data->display);
	if (str == FORK && (*data->alive == 1 || *data->alive == -2))
	{
		ft_display_time_name(data);
		ft_putstr(" has taken a fork\n");
	}
	else if (str == EAT && (*data->alive == 1 || *data->alive == -2))
	{
		ft_display_time_name(data);

		ft_putstr(" is eating\n");
	}
	else if (str == SLEEP && (*data->alive == 1 || *data->alive == -2))
	{
		ft_display_time_name(data);
		ft_putstr(" is sleeping\n");
	}
	else if (str == THINK && (*data->alive == 1 || *data->alive == -2))
	{
		ft_display_time_name(data);
		ft_putstr(" is thinking\n");
	}
	else if (str == DEATH && *data->alive == 1)
	{
		ft_display_time_name(data);
		*data->alive = -1;
		ft_putstr(" died\n");
	}
	pthread_mutex_unlock(data->display);
}
