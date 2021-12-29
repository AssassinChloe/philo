/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:38:06 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/29 17:49:32 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *err)
{
	printf("Error %s\n", err);
	return (1);
}

void	ft_checklife(t_init *var, t_data *data)
{
	int	i;

	i = 0;
	while (*data[i].alive == 1)
	{
		ft_check_last_meal(&data[i]);
		i++;
		if (i == var->philosophers)
			i = 0;
	}
}

void	*fonction(void *arg)
{
	t_data		*data;

	data = (t_data *)arg;
	while (data->philo.meal != 0 && *data->alive == 1)
	{
		ft_fork(data);
		if (data->philo.meal > 0)
		{
			data->philo.meal--;
			if (*data->alive == 1 && data->philo.meal == 0)
			{
				*data->alive = -2;
				return (0);
			}
		}
		ft_sleep(data);
		ft_think(data);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	t_init	*var;

	if (argc != 5 && argc != 6)
		return (ft_error("nombre d'arguments"));
	var = malloc(sizeof(t_init));
	if (!var)
		return (ft_error("malloc"));
	if (ft_init_var(var, argv, argc) == 1)
		return (1);
	data = malloc(sizeof(t_data) * var->philosophers);
	if (!data)
	{
		free(var);
		return (ft_error("malloc"));
	}
	if (ft_init_data(data, var, argv, argc) == 1)
		return (ft_free(data, var));
	ft_checklife(var, data);
	ft_ending(var, data);
	return (0);
}
