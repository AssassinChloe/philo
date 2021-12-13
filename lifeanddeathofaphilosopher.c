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

ft_fork
{
    if (pthread_mutex_lock(&here.fork) != 0)
	    ft_error("mutex lock");
    ft_display_message(FORK);
}

ft_eat
{
    ft_fork();
    ft_display_message(EAT);
    usleep(philo.eat * 1000);
    if (pthread_mutex_unlock(&here.fork) != 0)
		ft_error("mutex unlock");
}
ft_sleep
{
    ft_display_message(SLEEP);
    usleep(philo.sleep * 1000);
}
ft_think
{
    ft_display_message(THINK);
}

ft_die
{
        if (pthread_mutex_lock(&here.fork) != 0)
	    ft_error("mutex lock");
        ft_display_message(DEAD);
    	if (pthread_mutex_unlock(&here.fork) != 0)
		ft_error("mutex unlock");
}