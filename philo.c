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

int ft_error(int err)
{
	printf("Error %d\n", err);
	exit(EXIT_FAILURE);
}

void *fonction(void *params)
{
	t_philo here;

	here = *(t_philo *)params;
	if (pthread_mutex_lock(&here.fork) != 0)
		ft_error(5);
	printf("%d Philo %d is thinking\n", ft_timer(&here.time), here.name);
	sleep(1);
	printf("%d starve to death at %d\n", here.name, ft_timer(&here.time));
	usleep(600);
	if (pthread_mutex_unlock(&here.fork) != 0)
		ft_error(6);
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

int main(int ac, char **av)
{
	int philosophers;
	int forks;
	pthread_t philo[philosophers];
	int		i;
	t_philo *params[philosophers];
	t_data plop;

  	gettimeofday(&plop.start, NULL);
	if (ac != 5 && ac != 6) 
	{
		printf("Error : Wrong number of argument\n");
		return (1);
	}
	i = 0;
	philosophers = ft_atoi(av[1]);

	while (i < philosophers)
	{
		params[i] = malloc(sizeof(t_philo));
	if (!params[i])
		ft_error(3);
		params[i]->die = ft_atoi(av[2]);
		params[i]->eat = ft_atoi(av[3]);
		params[i]->sleep = ft_atoi(av[4]);
		if (ac == 6)
			params[i]->meal = ft_atoi(av[5]);
		else
			params[i]->meal = -2;
		params[i]->name = i + 1;
		params[i]->time.start = plop.start;
		pthread_mutex_init(&params[i]->fork, NULL);
		if (pthread_create(&philo[i], NULL, &fonction, &params[i]) != 0)
			ft_error(0);
		i++;
	}
	i = 0;
	while (i < philosophers)
	{
		if (pthread_join(philo[i], NULL) != 0)
			ft_error(1);
		i++;
	}
//	ft_create_philo(philosophers, &params);
	i = 0;
	while (i < philosophers)
	{
		if (pthread_mutex_destroy(&params[i]->fork) != 0)
			ft_error(4);
		free(params[i]);
		i++;
	}

	return (0);
}