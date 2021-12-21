/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:38:06 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/21 19:15:52 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *err)
{
	printf("Error %s\n", err);
	exit(EXIT_FAILURE);
}

void	*isalive(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (*data->alive == 1)
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
		pthread_join(checklife, NULL);
		return (0);
	}
	while (data->philo.meal != 0 && *data->alive == 1)
	{
		ft_fork(data);
		if (data->philo.meal > 0)
		{
			data->philo.meal--;
			if (data->philo.meal == 0)
				*data->alive = -2;
		}
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
		ft_error("nombre d'arguments");
	var = malloc(sizeof(t_init));
	if (!var)
		ft_error("malloc var");
	ft_init_var(var, argv, argc);
	data = malloc(sizeof(t_data) * var->philosophers);
	if (!data)
		ft_error("malloc data");
	ft_init_data(data, var, argv, argc);
	ft_init_forks(data, var);
	ft_init_philo(data, var);
	ft_ending(var, data);
	return (0);
}
