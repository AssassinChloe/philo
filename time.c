/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:35:51 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/10 11:36:59 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	ft_timer(t_data *data)
{
    int sec;
    int usec;
    int ms;

    gettimeofday(&data->current, NULL);
    sec = (data->current.tv_sec - data->start.tv_sec) * 1000;
    usec = (data->current.tv_usec - data->start.tv_usec) / 1000;
    ms = sec + usec;
	return (ms);
}
