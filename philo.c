/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:38:06 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/21 16:30:36 by cassassi         ###   ########.fr       */
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
	while (*data->philo.deadoralive == 1)
	{
		usleep(9000);
		ft_check_last_meal(data);
	}
	return (0);
}

void	*fonction(void *arg)
{
	t_data	*data;
	pthread_t checklife;

	data = (t_data *)arg;
	pthread_create(&checklife, NULL, &isalive, data);
	if (data->philo.borrow == NULL)
	{
		pthread_join(checklife, NULL);
		return (0);
	}
	while (data->philo.meal != 0 && *data->philo.deadoralive == 1)
	{
		ft_fork(data);
		if (data->philo.meal > 0)
		{
			data->philo.meal--;
			if (data->philo.meal == 0)
				*data->philo.deadoralive = -2;
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
	pthread_t	*th;
	struct timeval	start;
	int	i;
	int	error;
	int	philosophers;
	int	*dead;
	pthread_mutex_t	*display;

	if (argc != 5 && argc != 6)
		ft_error("nombre d'arguments");
	philosophers = ft_atoi(argv[1]);
	data = malloc(sizeof(t_data) * philosophers);
	th = malloc(sizeof(pthread_t) * philosophers);
	dead = malloc(sizeof(int));
	display = malloc(sizeof(pthread_mutex_t));
	if (!th || !data || !dead || !display)
		ft_error("malloc th/data/dead");
	*dead = 1;
	pthread_mutex_init(display, NULL);
	gettimeofday(&start, NULL);
	i = 0;
	while (i < philosophers)
	{	
		data[i].display = display;

		data[i].die = ft_atoi(argv[2]);
		data[i].eat = ft_atoi(argv[3]);
		data[i].sleep = ft_atoi(argv[4]);
		data[i].philo.name = i + 1;
		data[i].philo.deadoralive = dead;
		if (argc == 6)
			data[i].philo.meal = ft_atoi(argv[5]);
		else
			data[i].philo.meal = -1;		
		pthread_mutex_init(&data[i].philo.fork, NULL);
		data[i].display = display;
		data[i].time.start = start;
		data[i].philo.last_meal = malloc(sizeof(struct timeval));
		if (!data[i].philo.last_meal)
			ft_error("malloc tv");
		*data[i].philo.last_meal = start;
		i++;
	}
	i = 0;
	while (i < philosophers)
	{
		if (philosophers == 1)
			data[i].philo.borrow =  NULL;
		else if (i == (philosophers - 1))
			data[i].philo.borrow = &data[0].philo.fork;
		else
			data[i].philo.borrow = &data[i + 1].philo.fork;
		i++;
	}
	i = 0;
	while (i < philosophers)
	{	
		if (pthread_create(&th[i], NULL, &fonction, &data[i]) != 0)
			ft_error("pthread create");
		i++;
		usleep(50);
	}
	i = 0;
	while (i < philosophers)
	{
		pthread_join(th[i], NULL);
		i++;
	}
	i = 0;
	while (i < philosophers)
	{
		free(data[i].philo.last_meal);
		pthread_mutex_destroy(&data[i].philo.fork);
		i++;
	}
	pthread_mutex_destroy(display);
	free(display);
	free(data);
	free(th);
	free(dead);
	return (0);
}
