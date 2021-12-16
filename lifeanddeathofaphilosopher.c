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
    pthread_mutex_lock(&data->philo.fork);
    pthread_mutex_lock(data->philo.borrow);
    ft_display_message(FORK, data);
    data->philo.last_meal = ft_last_meal(data);
    ft_eat(data);
    if (pthread_mutex_unlock(&data->philo.fork) != 0)
		ft_error("mutex fork unlock");
	if (pthread_mutex_unlock(data->philo.borrow) != 0)
	    ft_error("mutex borrow unlock");
}

void ft_eat(t_data *data)
{
    //data->philo.i = data->eat;
    ft_display_message(EAT, data);

    // while (*data->philo.deadoralive == 1 && data->philo.i > 0)
    // {    
    //     if (data->philo.i > 10)
    //     {
    //         usleep(10000);
    //         data->philo.i -= 10;
    //         ft_last_meal(data);
    //     }
    //     else
    //     {
    //         usleep(data->philo.i * 1000);
    //         data->philo.i = 0;
    //     }
    // }
    usleep(data->eat * 1000);
}
void ft_sleep(t_data *data)
{
    // data->philo.i = data->sleep;
    ft_display_message(SLEEP, data);
    ft_last_meal(data);
    // while (*data->philo.deadoralive == 1 && data->philo.i > 0)
    // {
    //     if (data->philo.i > 10)
    //     {
    //         usleep(10000);
    //         data->philo.i = data->philo.i - 10;
    //         ft_last_meal(data);
    //     }
    //     else
    //     {
    //         usleep(data->philo.i*1000);
    //         data->philo.i = 0;
    //     }
    // }
    usleep(data->sleep * 1000);
}
void ft_think(t_data *data)
{
    ft_display_message(THINK, data);
}

void    ft_die(t_data *data)
{
        ft_display_message(DEATH, data);
        return ;
}