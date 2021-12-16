/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puttext.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cassassi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 15:08:52 by cassassi          #+#    #+#             */
/*   Updated: 2021/12/16 15:08:56 by cassassi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	unsigned int	i;

	i = 0;
	if (!(s))
		return ;
	while (s[i])
	{
		ft_putchar(s[i]);
		i++;
	}
}

void	ft_putnbr(int n)
{
	long long int	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
	{
		ft_putnbr(nb / 10);
		ft_putchar(nb % 10 + '0');
	}
	else
		ft_putchar(nb + '0');
}

