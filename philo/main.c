/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 18:45:57 by amanchon          #+#    #+#             */
/*   Updated: 2021/11/20 18:46:38 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_philo(pthread_t *thread_philo, t_philo *philo, int i)
{
	if (philo == NULL)
	{
		free(philo->table->forks);
		free(thread_philo);
		return (1);
	}
	philo->num = i + 1;
	if (pthread_mutex_init(&philo->mange_ou_creve, NULL))
	{
		ft_putstr_fd("Philo: mutex_init a échoué\n", 2);
		free(philo->table->forks);
		free(philo);
		free(thread_philo);
		return (1);
	}
	if (pthread_create(&thread_philo[i], NULL, vie_dun_philo, philo))
	{
		ft_putstr_fd("Philo: pthread_create a échoué\n", 2);
	}
	return (0);
}

void	att_philo_et_nettoyer_table(pthread_t *thread_philo,
			t_table *table, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
		pthread_join(thread_philo[i++], NULL);
	i = 0;
	while (i < nb_philo)
		pthread_mutex_destroy(&table->forks[i++]);
	pthread_mutex_destroy(&table->stylo);
	free(table->forks);
	free(thread_philo);
	return ;
}

int	main(int ac, char **av)
{
	t_data			data;
	t_table			table;
	pthread_t		*thread_philo;
	int				i;
	int				mort;

	i = -1;
	mort = 0;
	thread_philo = init_args(ac, &av, &data, &table);
	if (preparer_table(data.nb_philo, &table) == 1)
	{
		free(thread_philo);
		exit(1);
	}
	while (++i < data.nb_philo)
	{
		if (start_philo(thread_philo, creer_philo(&table, &mort, &data),
				i) == 1)
			exit(1);
	}
	att_philo_et_nettoyer_table(thread_philo, &table, data.nb_philo);
	exit(0);
}
