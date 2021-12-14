/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:38:06 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/08 15:50:58 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_error(char *err)
{
	printf("Error %s\n", err);
	exit(EXIT_FAILURE);
}

void *fonction(void *arg)
{
	t_data data = *(t_data *)arg;
    while(data.philo.meal > 0)
	{
	if (pthread_mutex_lock(&data.philo.fork) != 0)
	    ft_error("mutex lock");
    if (pthread_mutex_lock(&data.philo.borrow) != 0)
	    ft_error("mutex lock");
	ft_fork(&data);
    if (pthread_mutex_unlock(&data.philo.fork) != 0)
		ft_error("mutex unlock");
	if (pthread_mutex_unlock(&data.philo.borrow) != 0)
	    ft_error("mutex unlock"); 
	ft_sleep(&data);
	ft_think(&data);
	data.philo.meal--;
	}
	return (0);
}


void	mutex(pthread_mutex_t *fork)
{
	fork = malloc(sizeof(pthread_mutex_t));
	if (!fork)
		ft_error("malloc mutex");
}

void	borrow(t_data *data, int philo_nb)
{
	int i;

	i = 0;
	
	while (i < (philo_nb - 1))
	{
			data[i].philo.borrow = data[i + 1].philo.fork;
			i++;
	}
	data[(philo_nb - 1)].philo.borrow = data[0].philo.fork;
}

int 	main(int argc, char **argv)
{
	t_data *data;
	pthread_t *th;
	struct timeval start;
	int i;
	int error;
	int philosophers;

	if (argc != 5 && argc != 6)
		ft_error("nombre d'arguments");
	gettimeofday(&start, NULL);
	philosophers = ft_atoi(argv[1]);
	data = malloc(sizeof(t_data) * philosophers);
	th = malloc(sizeof(pthread_t) * philosophers);
	if (!th || !data)
		ft_error("malloc th/data");
	i = 0;
	while (i < philosophers)
	{
		data[i].time.start = start;
		data[i].die = ft_atoi(argv[2]);
		data[i].eat = ft_atoi(argv[3]);
		data[i].sleep = ft_atoi(argv[4]);
		data[i].philo.name = i + 1;
		if (argc == 6)
			data[i].philo.meal = ft_atoi(argv[5]);		

		data[i].philo.deadoralive = 1;
		mutex(&data[i].philo.fork);
		pthread_mutex_init(&data[i].philo.fork, NULL);
		i++;
	}
	borrow(data, philosophers);
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
		error = pthread_join(th[i], NULL);
		if (error != 0)
		{
			printf("%d ", error);
			ft_error("pthread join");
		}
		usleep(50);
		i++;
	}
	i = 0;
	while (i < philosophers)
	{
		if (pthread_mutex_destroy(&data[i].philo.fork) != 0)
			ft_error("mutex destroy");
		i++;
	}
	free(data);
	free(th);
	return (0);
}