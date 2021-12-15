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
	//return(0);
}

void *fonction(void *arg)
{
	t_data *data = (t_data *)arg;
	
    while(data->philo.meal > 0 && *data->philo.deadoralive == 1)
	{
		
		//printf("Left meals for %d = %d\n", data->philo.name, data->philo.meal);
		/*printf("%d fork : %p, borrow %p\n", data->philo.name, &data->philo.fork, data->philo.borrow);*/
		ft_fork(data);
 		ft_sleep(data);
		ft_think(data);
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
	gettimeofday(&start, NULL);
	philosophers = ft_atoi(argv[1]);
	data = malloc(sizeof(t_data) * philosophers);
	th = malloc(sizeof(pthread_t) * philosophers);
	dead = malloc(sizeof(int));
	display = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(display, NULL);
	*dead = 1;
	if (!th || !data || !dead)
		ft_error("malloc th/data/dead");
	i = 0;
	while (i < philosophers)
	{	
		data[i].display = display;
		data[i].time.start = start;
		data[i].die = ft_atoi(argv[2]);
		data[i].eat = ft_atoi(argv[3]);
		data[i].sleep = ft_atoi(argv[4]);
		data[i].philo.name = i + 1;
		data[i].philo.deadoralive = dead;
		if (argc == 6)
			data[i].philo.meal = ft_atoi(argv[5]);		
		gettimeofday(&data->philo.last_meal, NULL);
		mutex(&data[i].philo.fork);
		pthread_mutex_init(&data[i].philo.fork, NULL);
		i++;
	}
	i = 0;
	while (i < (philosophers))
	{
		if (i == (philosophers - 1))
			data[i].philo.borrow = &data[0].philo.fork;
		else
			data[i].philo.borrow = &data[i + 1].philo.fork;
		i++;
	}
	
	i = 0;
	while (i < philosophers)
	{
	//	printf("%d fork : %p, borrow %p\n", data[i].philo.name, &data[i].philo.fork, data[i].philo.borrow);
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
	if (pthread_mutex_destroy(display) != 0)
		ft_error("mutex display destroy");
	free(data);
	free(th);
	free(dead);
	return (0);
}