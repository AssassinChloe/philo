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

int ft_error()
{
	printf("Error\n");
	exit(EXIT_FAILURE);
}

void *fonction(void *params)
{
	t_philo *here;

	here = (t_philo *)params;
	if (pthread_mutex_lock(&here->fork) != 0)
		ft_error();
	printf("%d Philo %d is thinking and letting himself starve to death, sorry \n", ft_timer(&here->time), here->name);
	usleep(500);
	if (pthread_mutex_unlock(&here->fork) != 0)
		ft_error();
	return (0);
}

void ft_create_philo(int philosophers, t_philo *params)
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
}

int main(int ac, char **av)
{
	int philosophers;
	int forks;
	t_philo params;

  	gettimeofday(&params.time.start, NULL);
	if (ac != 5 && ac != 6) 
	{
		printf("Error : Wrong number of argument\n");
		return (1);
	}
	philosophers = ft_atoi(av[1]);
	params.die = ft_atoi(av[2]);
	params.eat = ft_atoi(av[3]);
	params.sleep = ft_atoi(av[4]);
	if (ac == 6)
		params.meal = ft_atoi(av[5]);
	else
		params.meal = -2;
	forks = philosophers;
	pthread_mutex_init(&params.fork, NULL);
	ft_create_philo(philosophers, &params);
	if (pthread_mutex_destroy(&params.fork) != 0)
		ft_error();
	return (0);
}
