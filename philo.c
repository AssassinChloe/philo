/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:38:06 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/28 20:18:04 by cassassi         ###   ########.fr       */
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
	t_data	**data;
	int i;

	i = 0;
	data = (t_data **)arg;
	while (i < data[i]->philo_nb && *data[i]->alive == 1)
	{
		ft_check_last_meal(data[i]);
		i++;
		if (i == data[i]->philo_nb)
			i = 0;
	}
	return (0);
}

int	ft_meal(t_data *data)
{
	if (data->philo.meal > 0)
	{
		data->philo.meal--;
		if (data->philo.meal == 0)
		{
			*data->alive = -2;
			return (1);
		}
	}
	return (0);
}

void	*fonction(void *arg)
{
	t_data		*data;

	data = (t_data *)arg;
	if (data->philo.borrow == NULL)
	{
		pthread_mutex_lock(&data->philo.fork);
		ft_display_message(FORK, data);
		usleep(data->die * 1000);
		ft_check_last_meal(data);
		pthread_mutex_unlock(&data->philo.fork);
		return (0);
	}
	while (data->philo.meal != 0 && *data->alive == 1)
	{
		ft_fork(data);
		if (ft_meal(data) == 1)
			return (0);
		ft_sleep(data);
		ft_think(data);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_init	*var;
	pthread_t	checklife;

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
	pthread_create(&checklife, NULL, &isalive, &data);
	if (ft_init_data(data, var, argv, argc) == 1)
		return (ft_free(data, var));
	pthread_join(checklife, NULL);
	ft_ending(var, data);

	return (0);
}
