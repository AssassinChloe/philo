/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:38:06 by cassassi          #+#    #+#             */
/*   Updated: 2022/01/11 16:03:32 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *err)
{
	printf("Error %s\n", err);
	return (1);
}

void	philo_life(t_data *data)
{
	ft_fork(data);
	ft_sleep(data);
	ft_think(data);
}

void	*the_matrix(void *arg)
{
	t_data		*data;

	data = (t_data *)arg;
	if (data->philo.borrow == NULL)
	{
		ft_display_message(FORK, data);
		return (0);
	}
	while (1)
	{
		pthread_mutex_lock(data->check_vitals);
		if (*data->end_simulation == 1)
		{
			pthread_mutex_unlock(data->check_vitals);
			return (0);
		}
		else
			pthread_mutex_unlock(data->check_vitals);
		philo_life(data);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	**data;
	t_init	*var;

	if (argc != 5 && argc != 6)
		return (ft_error("nombre d'arguments"));
	var = malloc(sizeof(t_init));
	if (!var)
		return (ft_error("malloc"));
	if (ft_init_var(var, argv) == 1)
	{
		free(var);
		return (1);
	}
	data = malloc(sizeof(t_data) * var->philosophers);
	if (!data)
	{
		free(var);
		return (ft_error("malloc"));
	}
	if (ft_init_data(data, var, argv, argc) == 1)
		return (ft_free(data, var));
	ft_check_vitals(data, var->philosophers);
	ft_ending(var, data);
	return (0);
}
