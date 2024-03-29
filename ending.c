/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:59:52 by cassassi          #+#    #+#             */
/*   Updated: 2022/01/11 15:02:18 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_free(t_data **data, t_init *var)
{
	if (var->display)
		free(var->display);
	if (var->check_vitals)
		free(var->check_vitals);
	if (var->th)
		free(var->th);
	if (var->dead)
		free(var->dead);
	if (data)
		free(data);
	if (var)
		free(var);
	return (1);
}

void	ft_ending(t_init *var, t_data **data)
{
	int	i;

	i = 0;
	while (i < var->philosophers)
	{
		pthread_join(var->th[i], NULL);
		i++;
	}
	i = 0;
	while (i < var->philosophers)
	{
		if (data[i]->philo.last_meal)
			free(data[i]->philo.last_meal);
		pthread_mutex_destroy(&data[i]->philo.fork);
		free(data[i]);
		i++;
	}
	pthread_mutex_destroy(var->display);
	pthread_mutex_destroy(var->check_vitals);
	ft_free(data, var);
}
