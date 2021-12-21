/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ending.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/21 17:59:52 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/21 19:16:19 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_ending(t_init *var, t_data *data)
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
		free(data[i].philo.last_meal);
		pthread_mutex_destroy(&data[i].philo.fork);
		i++;
	}
	pthread_mutex_destroy(var->display);
	free(var->display);
	free(var->th);
	free(var->dead);
	free(data);
	free(var);
}
