/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creer_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 18:45:57 by amanchon          #+#    #+#             */
/*   Updated: 2021/11/20 18:46:38 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	creer_philo2(t_philo *philotmp, t_table *table, int *mort, t_data *data)
{
	philotmp->mains[0] = 0;
	philotmp->mains[1] = 0;
	philotmp->mort = mort;
	philotmp->table = table;
	philotmp->data = data;
	philotmp->nb_repas = 0;
	return ;
}

t_philo	*creer_philo(t_table *table, int *mort, t_data *data)
{
	t_philo		*philo;
	t_philo		*philo_tmp;
	int			i;

	i = -1;
	philo = malloc(sizeof(t_philo) * data->nb_philo);
	if (philo == NULL)
	{
		ft_putstr_fd("Philo: malloc a échoué\n", 2);
		return (NULL);
	}
	while (++i < data->nb_philo)
	{
		philo_tmp = &philo[i];
		philo_tmp->num = i + 1;
		creer_philo2(philo_tmp, table, mort, data);
		if (pthread_mutex_init(&philo_tmp->mange_ou_creve, NULL))
		{
			ft_putstr_fd("Philo: mutex_init a échoué\n", 2);
			free(philo);
			return (NULL);
		}
	}
	return (philo);
}
