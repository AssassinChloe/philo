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

void *fonction(void * arg)
{
	t_philo here = *(t_philo *)arg;
	if (pthread_mutex_lock(&here.fork) != 0)
		ft_error("mutex lock");
	printf("%d Philo %d is thinking\n", ft_timer(&here.time), here.name);
	sleep(1);
	printf("%d starve to death at %d\n", here.name, ft_timer(&here.time));
	usleep(600);
	if (pthread_mutex_unlock(&here.fork) != 0)
		ft_error("mutex unlock");
	return (0);
}

/*void ft_create_philo(int philosophers, t_philo *params)
{
	pthread_t philo[philosophers];
	int		i;

	i = 0;
	while (i < philosophers)
	{
		
		if (pthread_create(&philo[i], NULL, &fonction, params) != 0)
			ft_error();
		i++;
	}
	i = 0;
	while (i < philosophers)

	{
		if (pthread_join(philo[i], NULL) != 0)
			ft_error();
		i++;
	}
}*/

void	mutex(pthread_mutex_t *fork)
{
	fork = malloc(sizeof(pthread_mutex_t));
	if (!fork)
		ft_error("malloc mutex");
}

int main(int argc, char **argv)
{
	t_philo *philo;
	t_time timestamp;
	pthread_t thread;

  	gettimeofday(&timestamp.start, NULL);
	printf("%d : Starting\n", ft_timer(&timestamp));
	philo = malloc(sizeof(t_philo));
	if (!philo)
		ft_error("malloc t_philo");
	philo->name = 1;
	philo->time.start = timestamp.start;
	philo->die = ft_atoi(argv[2]);
	philo->eat = ft_atoi(argv[3]);
	philo->sleep = ft_atoi(argv[4]);
	if (argc == 6)
	philo->meal = ft_atoi(argv[5]);
	mutex(&philo->fork);
	pthread_mutex_init(&philo->fork, NULL);
	if (pthread_create(&thread, NULL, &fonction, philo) != 0)
		ft_error("pthread create");
	if (pthread_join(thread, NULL) != 0)
		ft_error("pthread join");
	if (pthread_mutex_destroy(&philo->fork) != 0)
		ft_error("mutex destroy");
	free(philo);
	return (0);
}