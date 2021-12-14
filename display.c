/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 15:13:12 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/13 15:13:16 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    ft_display_message(int str, t_data *data)
{
    if (str == FORK)
        printf("%d %d has taken a fork\n", ft_timer(&data->time), data->philo.name);
    else if (str == EAT)
        printf("%d %d is eating\n", ft_timer(&data->time), data->philo.name);
    else if (str == SLEEP)
        printf("%d %d is sleeping\n", ft_timer(&data->time), data->philo.name);
    else if (str == THINK)
        printf("%d %d is thinking\n", ft_timer(&data->time), data->philo.name);
    else if (str == DEATH)
        printf("%d %d died\n", ft_timer(&data->time), data->philo.name);

}