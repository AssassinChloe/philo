/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 16:18:04 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/21 19:23:02 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philo(t_data *data, t_init *var)
{
	int	i;

	i = 0;
	while (i < var->philosophers)
	{	
		if (pthread_create(&var->th[i], NULL, &fonction, &data[i]) != 0)
			ft_error("pthread create");
		i++;
		usleep(50);
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

void	ft_init_var(t_init *var, char **argv, int argc)
{
	var->philosophers = ft_atoi(argv[1]);
	var->th = malloc(sizeof(pthread_t) * var->philosophers);
	var->dead = malloc(sizeof(int));
	var->display = malloc(sizeof(pthread_mutex_t));
	if (!var->th || !var->dead || !var->display)
		ft_error("malloc th/dead/display");
	*var->dead = 1;
	pthread_mutex_init(var->display, NULL);
	gettimeofday(&var->init_time, NULL);
}

void	ft_init_data(t_data *data, t_init *var, char **argv, int argc)
{
	int	i;

	i = 0;
	while (i < var->philosophers)
	{	
		data[i].display = var->display;
		data[i].die = ft_atoi(argv[2]);
		data[i].eat = ft_atoi(argv[3]);
		data[i].sleep = ft_atoi(argv[4]);
		data[i].philo.name = i + 1;
		data[i].alive = var->dead;
		if (argc == 6)
			data[i].philo.meal = ft_atoi(argv[5]);
		else
			data[i].philo.meal = -1;
		pthread_mutex_init(&data[i].philo.fork, NULL);
		data[i].time.start = var->init_time;
		data[i].philo.last_meal = malloc(sizeof(struct timeval));
		if (!data[i].philo.last_meal)
			ft_error("malloc tv");
		*data[i].philo.last_meal = var->init_time;
		i++;
	}
}
