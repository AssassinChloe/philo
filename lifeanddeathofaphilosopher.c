/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifeanddeathofaphilosopher.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:59:15 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/13 14:59:29 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_fork(t_data *data)
{
    if (pthread_mutex_lock(&data->philo.fork) != 0)
	    ft_error("mutex fork lock");
    if (pthread_mutex_lock(data->philo.borrow) != 0)
	    ft_error("mutex borrow lock");
    data->philo.last_meal = ft_last_meal(data);
    ft_display_message(FORK, data);
    ft_eat(data);
    if (pthread_mutex_unlock(&data->philo.fork) != 0)
		ft_error("mutex fork unlock");
	if (pthread_mutex_unlock(data->philo.borrow) != 0)
	    ft_error("mutex borrow unlock");
}

void ft_eat(t_data *data)
{
    ft_last_meal(data);
    ft_display_message(EAT, data);
    usleep(data->eat * 1000);
}
void ft_sleep(t_data *data)
{
    ft_last_meal(data);
    ft_display_message(SLEEP, data);
    usleep(data->sleep * 1000);
}
void ft_think(t_data *data)
{
    ft_last_meal(data);
    ft_display_message(THINK, data);
}

void    ft_die(t_data *data)
{
        ft_display_message(DEATH, data);
}