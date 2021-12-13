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


int	ft_timer(t_time *time)
{
    long long sec;
    long long usec;
    int ms;

    gettimeofday(&time->current, NULL);
    sec = (time->current.tv_sec - time->start.tv_sec) * 1000;
    usec = (time->current.tv_usec - time->start.tv_usec) / 1000;
    ms = sec + usec;
	return (ms);
}
