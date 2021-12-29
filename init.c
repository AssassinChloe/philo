/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:18:04 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/22 14:25:03 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philo(t_data *data, t_init *var)
{
	int	i;

	i = 0;
	while (i < var->philosophers)
	{	
		pthread_create(&var->th[i], NULL, &fonction, &data[i]);
		i++;
		usleep(10);
	}
}

void	ft_init_forks(t_data *data, t_init *var)
{
	int	i;

	i = 0;
	while (i < var->philosophers)
	{
		if (var->philosophers == 1)
			data[i].philo.borrow = NULL;
		else if (i == (var->philosophers - 1))
			data[i].philo.borrow = &data[0].philo.fork;
		else
			data[i].philo.borrow = &data[i + 1].philo.fork;
		i++;
	}
}

int	ft_init_var(t_init *var, char **argv, int argc)
{
	var->philosophers = ft_atoi(argv[1]);
	if (var->philosophers <= 0)
		return (ft_error("number of philosophers invalid"));
	var->th = malloc(sizeof(pthread_t) * var->philosophers);
	var->dead = malloc(sizeof(int));
	var->display = malloc(sizeof(pthread_mutex_t));
	if (!var->th || !var->dead || !var->display)
		return (ft_error("malloc"));
	*var->dead = 1;
	pthread_mutex_init(var->display, NULL);
	gettimeofday(&var->init_time, NULL);
	return (0);
}

int	ft_init_data_2(t_data *data, t_init *var, int i)
{
	data[i].display = var->display;
	data[i].philo.name = i + 1;
	data[i].alive = var->dead;
	data[i].time.start = var->init_time;
	data[i].philo.last_meal = malloc(sizeof(struct timeval));
	if (!data[i].philo.last_meal)
		return (ft_error("malloc"));
	*data[i].philo.last_meal = var->init_time;
	pthread_mutex_init(&data[i].philo.fork, NULL);
	return (0);
}

int	ft_init_data(t_data *data, t_init *var, char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < var->philosophers)
	{	
		data[i].eat = ft_atoi(argv[3]);
		data[i].sleep = ft_atoi(argv[4]);
		data[i].die = ft_atoi(argv[2]);
		if (data[i].die <= 0 || data[i].eat <= 0 || data[i].sleep <= 0)
			return (ft_error("some time arg are invalid"));
		if (argc == 6)
		{
			data[i].philo.meal = ft_atoi(argv[5]) + 1;
			if (data[i].philo.meal <= 1)
				return (ft_error("number of meals invalid"));
		}
		else
			data[i].philo.meal = -1;
		if (ft_init_data_2(data, var, i) == 1)
			return (1);
		i++;
	}
	ft_init_forks(data, var);
	ft_init_philo(data, var);
	return (0);
}
