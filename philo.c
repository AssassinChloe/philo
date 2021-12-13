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

	if (pthread_mutex_lock(&data.philo[0].m_fork) != 0)
		ft_error("mutex lock");
	printf("%d Philo %d is thinking\n", ft_timer(&data.time), data.philo[0].name);
	usleep(500);
	printf("%d %d starve to death\n", ft_timer(&data.time), data.philo[0].name);
	if (pthread_mutex_unlock(&data.philo[0].m_fork) != 0)
		ft_error("mutex unlock");
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
	t_data data;
	pthread_t th[data.philo_nb];
	int i;
	int error;

	gettimeofday(&data.time.start, NULL);
	printf("%d : Starting\n", ft_timer(&data.time));
	data.philo_nb = ft_atoi(argv[1]);
	data.die = ft_atoi(argv[2]);
	data.eat = ft_atoi(argv[3]);
	data.sleep = ft_atoi(argv[4]);
	data.philo = malloc(sizeof(t_philo) * data.philo_nb);
	if (!data.philo)
		ft_error("malloc data.philo");
	i = 0;
	while (i < data.philo_nb)
	{
		data.philo[i].name = i + 1;
		if (argc == 6)
			data.philo[i].meal = ft_atoi(argv[5]);		
		data.philo[i].deadoralive = 1;
		mutex(&data.philo[i].m_fork);
		pthread_mutex_init(&data.philo[i].m_fork, NULL);
		if (pthread_create(&th[i], NULL, &fonction, &data) != 0)
			ft_error("pthread create");
			i++;
	}
	i = 0;
	sleep(3);
	while (i < data.philo_nb)
	{
		error = pthread_join(th[i], NULL);
		if (error != 0)
		{
			printf("%d ", error);
			ft_error("pthread join");
		}
		i++;
	}
	sleep(3);
	i = 0;
	while (i < data.philo_nb)
	{
		if (pthread_mutex_destroy(&data.philo[i].m_fork) != 0)
			ft_error("mutex destroy");
		i++;
	}
	free(data.philo);
	return (0);
}