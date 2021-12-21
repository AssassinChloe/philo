/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:38:06 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/21 09:38:37 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_error(char *err)
{
	printf("Error %s\n", err);
	exit(EXIT_FAILURE);
}

void *	isalive(void *arg)
{
	t_data * data = (t_data *)arg;
	usleep(data->die * 1000);
	ft_check_last_meal(data);
	return (0);
}

void *fonction(void *arg)
{
	t_data *data = (t_data *)arg;
	pthread_t checklife;
	
    while(data->philo.meal != 0 && *data->philo.deadoralive == 1)
	{
		pthread_create(&checklife, NULL, &isalive, data);
		if (data->philo.borrow == NULL)
		{
			pthread_join(checklife, NULL);
			return (0);
		}
		ft_fork(data);
 		ft_sleep(data);
		ft_think(data);
		if (data->philo.meal > 0)
			data->philo.meal--;
	}
	return (0);
}


void	mutex(pthread_mutex_t *fork)
{
	fork = malloc(sizeof(pthread_mutex_t));
	if (!fork)
		ft_error("malloc mutex");
}

int 	main(int argc, char **argv)
{
	t_data *data;
	pthread_t *th;
	struct timeval start;
	int i;
	int error;
	int philosophers;
	int *dead;
	pthread_mutex_t *display;

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
		mutex(&data[i].philo.fork);
		pthread_mutex_init(&data[i].philo.fork, NULL);
		data[i].display = display;
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
	gettimeofday(&start, NULL);
	i = 0;
	while (i < philosophers)
	{	
		data[i].time.start = start;
		data[i].philo.last_meal = &start;
		if (pthread_create(&th[i], NULL, &fonction, &data[i]) != 0)
			ft_error("pthread create");
		i++;
	}
	i = 0;
	while (i < philosophers)
	{
		error = pthread_join(th[i], NULL);
		if (error != 0)
		{
			printf("%d ", error);
			ft_error("pthread join");
		}
		i++;
	}
	i = 0;
	while (i < philosophers)
	{
		pthread_mutex_destroy(&data[i].philo.fork);
		i++;
	}
	pthread_mutex_destroy(display);
	free(data);
	free(th);
	free(dead);
	return (0);
}
