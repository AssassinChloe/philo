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

    ft_display_message(FORK, data);
    ft_eat(data);


}

void ft_eat(t_data *data)
{
    ft_display_message(EAT, data);
    usleep(data->eat * 1000);
}
void ft_sleep(t_data *data)
{
    ft_display_message(SLEEP, data);
    usleep(data->sleep * 1000);
}
void ft_think(t_data *data)
{
    ft_display_message(THINK, data);
}
/*
ft_die
{
        if (pthread_mutex_lock(&here.fork) != 0)
	    ft_error("mutex lock");
        ft_display_message(DEATH);
    	if (pthread_mutex_unlock(&here.fork) != 0)
		ft_error("mutex unlock");
}*/