/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:18:04 by cassassi          #+#    #+#             */
/*   Updated: 2022/01/11 15:32:23 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_forks(t_data **data, t_init *var)
{
	int	i;

	i = 0;
	while (i < var->philosophers)
	{
		if (var->philosophers == 1)
			data[i]->philo.borrow = NULL;
		else if (i == (var->philosophers - 1))
			data[i]->philo.borrow = &data[0]->philo.fork;
		else
			data[i]->philo.borrow = &data[i + 1]->philo.fork;
		i++;
	}
}

int	ft_init_data_2(t_data **data, t_init *var, int i)
{
	data[i]->display = var->display;
	data[i]->check_vitals = var->check_vitals;
	data[i]->philo.name = i + 1;
	data[i]->end_simulation = var->dead;
	data[i]->time.start = var->init_time;
	data[i]->philo.last_meal = malloc(sizeof(struct timeval));
	if (!data[i]->philo.last_meal)
		return (ft_error("malloc"));
	*data[i]->philo.last_meal = var->init_time;
	pthread_mutex_init(&data[i]->philo.fork, NULL);
	pthread_mutex_init(&data[i]->philo.meal_m, NULL);
	return (0);
}

int	ft_check_arg(char **argv, int argc, t_data **data, int i)
{
	data[i]->eat = ft_atoi(argv[3]);
	data[i]->sleep = ft_atoi(argv[4]);
	data[i]->die = ft_atoi(argv[2]);
	if (data[i]->die <= 0 || data[i]->eat <= 0 || data[i]->sleep <= 0)
	{
		free(data[i]);
		return (ft_error("some time arg are invalid"));
	}
	if (argc == 6)
	{
		data[i]->philo.meal = ft_atoi(argv[5]);
		if (data[i]->philo.meal <= 0)
		{
			free(data[i]);
			return (ft_error("number of meals invalid"));
		}
	}
	else
		data[i]->philo.meal = -1;
	return (0);
}

int	ft_init_data(t_data **data, t_init *var, char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < var->philosophers)
	{
		data[i] = malloc(sizeof(t_data));
		if (ft_check_arg(argv, argc, data, i) == 1)
			return (1);
		if (ft_init_data_2(data, var, i) == 1)
			return (1);
		i++;
	}
	ft_init_forks(data, var);
	return (0);
}

int	ft_init_var(t_init *var, char **argv)
{
	var->philosophers = ft_atoi(argv[1]);
	if (var->philosophers <= 0)
		return (ft_error("number of philosophers invalid"));
	var->th = malloc(sizeof(pthread_t) * var->philosophers);
	var->dead = malloc(sizeof(int));
	var->display = malloc(sizeof(pthread_mutex_t));
	var->check_vitals = malloc(sizeof(pthread_mutex_t));
	if (!var->th || !var->dead || !var->display || !var->check_vitals)
		return (ft_error("malloc"));
	*var->dead = 0;
	pthread_mutex_init(var->display, NULL);
	pthread_mutex_init(var->check_vitals, NULL);
	gettimeofday(&var->init_time, NULL);
	return (0);
}
