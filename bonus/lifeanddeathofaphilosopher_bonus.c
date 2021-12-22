/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifeanddeathofaphilosopher_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 14:59:15 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/22 11:27:43 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_fork(t_data *data)
{
	sem_wait(data->semaphore);
	ft_check_last_meal(data);
	ft_display_message(FORK, data);
	sem_wait(data->semaphore);
	ft_check_last_meal(data);
	ft_display_message(FORK, data);
	ft_eat(data);
	sem_post(data->semaphore);
	sem_post(data->semaphore);
}

void	ft_eat(t_data *data)
{
	ft_last_meal(data);
	ft_display_message(EAT, data);
	usleep((data->eat * 1000));
}

void	ft_sleep(t_data *data)
{
	ft_display_message(SLEEP, data);
	usleep(data->sleep * 1000);
	ft_check_last_meal(data);
}

void	ft_think(t_data *data)
{
	ft_display_message(THINK, data);
}

void	ft_die(t_data *data)
{
	ft_display_message(DEATH, data);
}
