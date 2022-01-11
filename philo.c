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

void	*isalive(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	while (1)
	{
		usleep(1000);
		pthread_mutex_lock(&data->philo.meal_m);
	       	if (data->philo.meal == 0 || *data->end_simulation == 1)
		{
			pthread_mutex_unlock(&data->philo.meal_m);
			return (0);
		}
		ft_check_last_meal(data);
		pthread_mutex_unlock(&data->philo.meal_m);
	}
	return (0);
}

void	*the_matrix(void *arg)
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
	while (1)
	{
		pthread_mutex_lock(&data->philo.meal_m);
	      	if (data->philo.meal == 0 || *data->end_simulation == 1)
		{
			pthread_mutex_unlock(&data->philo.meal_m);
			pthread_join(checklife, NULL);
			return (0);
		}
		pthread_mutex_unlock(&data->philo.meal_m);
		ft_fork(data);
		ft_sleep(data);
		ft_think(data);
	}
	pthread_join(checklife, NULL);
	return (0);
}

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
		if (data[i]->philo.alive == 0)
		{	
			*data[i]->end_simulation = 1;
			pthread_mutex_unlock(data[i]->display);
			return ;
		}
		if (ft_all_done_eating(data, philosophers) == 1)
			return ;
		i++;
		if (i == philosophers)
			i = 0;
	}
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
	if (ft_init_var(var, argv, argc) == 1)
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
