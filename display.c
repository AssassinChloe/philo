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
    if(pthread_mutex_lock(data->display) != 0)
        ft_error("lock display");
    if (str == FORK && *data->philo.deadoralive == 1)
    {
        ft_putnbr(ft_timer(&data->time));
        ft_putchar(' ');
        ft_putnbr(data->philo.name);
        ft_putstr(" has taken a fork\n");
    }
    else if (str == EAT && *data->philo.deadoralive == 1)
    {       
        ft_putnbr(ft_timer(&data->time));
        ft_putchar(' ');
        ft_putnbr(data->philo.name);
        ft_putstr(" is eating\n");
    }
    else if (str == SLEEP && *data->philo.deadoralive == 1)
        {       
        ft_putnbr(ft_timer(&data->time));
        ft_putchar(' ');
        ft_putnbr(data->philo.name);
        ft_putstr(" is sleeping\n");
        } 
    else if (str == THINK && *data->philo.deadoralive == 1)
            {       
        ft_putnbr(ft_timer(&data->time));
        ft_putchar(' ');
        ft_putnbr(data->philo.name);
        ft_putstr(" is thinking\n");
    }
    else if (str == DEATH)
        {       
        ft_putnbr(ft_timer(&data->time));
        ft_putchar(' ');
        ft_putnbr(data->philo.name);
        ft_putstr(" died\n");
    }
    if(pthread_mutex_unlock(data->display) != 0)
        ft_error("unlock display");
}