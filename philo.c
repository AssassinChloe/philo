/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:38:06 by cassassi          #+#    #+#             */
/*   Updated: 2022/01/07 14:54:55 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *err)
{
	printf("Error %s\n", err);
	return (1);
}

void	*isalive(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (data->philo.meal != 0 && *data->alive == 1)
	{
		usleep(9000);
		ft_check_last_meal(data);
	}
	return (0);
}

void	*fonction(void *arg)
{
	t_data		*data;
	pthread_t	checklife;

	data = (t_data *)arg;
	pthread_create(&checklife, NULL, &isalive, data);
	if (data->philo.borrow == NULL)
	{
		ft_display_message(FORK, data);
		pthread_join(checklife, NULL);
		return (0);
	}
	while (data->philo.meal != 0 && *data->alive == 1)
	{
		ft_fork(data);
		ft_sleep(data);
		ft_think(data);
	}
	pthread_join(checklife, NULL);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_init	*var;

	if (argc != 5 && argc != 6)
		return (ft_error("nombre d'arguments"));
	var = malloc(sizeof(t_init));
	if (!var)
		return (ft_error("malloc"));
	if (ft_init_var(var, argv, argc) == 1)
		return (1);
	data = malloc(sizeof(t_data) * var->philosophers);
	if (!data)
	{
		free(var);
		return (ft_error("malloc"));
	}
	if (ft_init_data(data, var, argv, argc) == 1)
		return (ft_free(data, var));
	ft_ending(var, data);
	return (0);
}
