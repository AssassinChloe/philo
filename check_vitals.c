/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vitals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:31:42 by cassassi          #+#    #+#             */
/*   Updated: 2022/03/01 18:32:09 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_all_done_eating(t_data **data, int philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers)
	{
		pthread_mutex_lock(&data[i]->philo.meal_m);
		if (data[i]->philo.meal != 0)
		{
			pthread_mutex_unlock(&data[i]->philo.meal_m);
			return (0);
		}
		pthread_mutex_unlock(&data[i]->philo.meal_m);
		i++;
	}
	return (1);
}

void	ft_check_vitals(t_data **data, int philosophers)
{
	int	i;

	i = 0;
	while (i < philosophers)
	{
		pthread_mutex_lock(data[i]->check_vitals);
		if (data[i]->philo.alive == 0)
		{	
			*data[i]->end_simulation = 1;
			pthread_mutex_unlock(data[i]->check_vitals);
			return ;
		}
		pthread_mutex_unlock(data[i]->check_vitals);
		if (ft_all_done_eating(data, philosophers) == 1)
			return ;
		i++;
		if (i == philosophers)
			i = 0;
	}
}