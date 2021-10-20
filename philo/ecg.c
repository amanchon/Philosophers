/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ecg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 18:45:57 by amanchon          #+#    #+#             */
/*   Updated: 2021/11/20 18:46:38 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ecg_suite(t_philo *philo)
{
	int		t_mort;

	if (*philo->mort == 1)
	{
		pthread_mutex_unlock(&philo->table->fin);
		return (1);
	}
	pthread_mutex_lock(&philo->mange_ou_creve);
	t_mort = mtn() - philo->t_dernier_repas;
	if (t_mort > philo->data->t_mourir)
	{
		philo_mort(philo);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->fin);
	if (philo->nb_repas == philo->data->nb_repas_max)
	{
		pthread_mutex_unlock(&philo->mange_ou_creve);
		return (1);
	}
	pthread_mutex_unlock(&philo->mange_ou_creve);
	return (0);
}

void	*ecg(void *info)
{
	t_philo	*philo;

	philo = (t_philo *)info;
	while (1)
	{
		pthread_mutex_lock(&philo->table->fin);
		if (ecg_suite(philo) == 1)
			return (NULL);
		usleep(4000);
	}
	return (NULL);
}
