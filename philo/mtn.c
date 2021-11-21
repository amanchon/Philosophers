/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtn.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 18:45:57 by amanchon          #+#    #+#             */
/*   Updated: 2021/11/20 18:46:38 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	mtn(void)
{
	struct timeval	mtntv;
	int				ms;

	gettimeofday(&mtntv, NULL);
	ms = (int)((mtntv.tv_usec / 1000) + (mtntv.tv_sec * 1000));
	return (ms);
}
