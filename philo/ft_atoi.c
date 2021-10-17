/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 16:56:47 by amanchon          #+#    #+#             */
/*   Updated: 2020/01/16 16:45:43 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	x;
	int	res;

	i = 0;
	x = 1;
	res = 0;
	while (str == NULL || str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
	{
		if (str == NULL || str[i] == '\0')
			return (0);
		i++;
	}
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			x = -1 * x;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (res * x);
}
