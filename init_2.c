/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 19:06:27 by cassassi          #+#    #+#             */
/*   Updated: 2022/03/01 19:06:30 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philo(t_data **data, t_init *var)
{
	int	i;

	i = 0;
	while (i < var->philosophers)
	{
		if (i % 2 == 0)
			pthread_create(&var->th[i], NULL, &the_matrix, data[i]);
		i++;
	}
	i = 0;
	usleep(1000);
	while (i < var->philosophers)
	{
		if (i % 2 != 0)
			pthread_create(&var->th[i], NULL, &the_matrix, data[i]);
		i++;
	}
}
