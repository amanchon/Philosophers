#include "philo.h"

int	routine_dun_philo_suite(t_philo *philo)
{
	if (sleep_philo(philo, philo->data->t_manger) == 1)
		return (1);
	lacher_forks(philo, philo->table);
	pthread_mutex_lock(&philo->mange_ou_creve);
	philo->nb_repas += 1;
	if (philo->nb_repas == philo->data->nb_repas_max)
	{
		pthread_mutex_unlock(&philo->mange_ou_creve);
		return (1);
	}
	pthread_mutex_unlock(&philo->mange_ou_creve);
	if (philo_copiste(philo, philo->num, mtn() - philo->depart, 3) == 1)
			return (1);
	if (sleep_philo(philo, philo->data->t_dormir) == 1)
		return (1);
	if (philo_copiste(philo, philo->num, mtn() - philo->depart, 4) == 1)
			return (1);
	return (0);
}

int	routine_dun_philo(t_philo *philo)
{
	int	depart;
	int	tps;

	depart = philo->depart;
	if (prendre_forks(philo, philo->table, philo->data->nb_philo) == 1)
		return (1);
	tps = mtn() - depart;
	if (philo_copiste(philo, philo->num, tps, 1) == 1)
			return (1);
	if (philo_copiste(philo, philo->num, tps, 2) == 1)
			return (1);
	philo->t_dernier_repas = mtn();
	pthread_mutex_unlock(&philo->mange_ou_creve);
	if (routine_dun_philo_suite(philo) == 1)
		return (1);
	return (0);
}

int	boucle_routine_philo(t_philo *philo)
{
	int		fin2;

	pthread_mutex_lock(&philo->table->fin);
	if (*philo->mort == 1)
	{
		pthread_mutex_unlock(&philo->table->fin);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->fin);
	fin2 = routine_dun_philo(philo);
	if (fin2 != 0)
	{
		lacher_forks(philo, philo->table);
		return (1);
	}
	return (0);
}

void	*vie_dun_philo(void *info)
{
	t_philo		*philo;
	pthread_t	thread_ecg;

	philo = (t_philo *)info;
	philo->depart = mtn();
	philo->t_dernier_repas = philo->depart;
	if (pthread_create(&thread_ecg, NULL, ecg, philo))
	{
		ft_putstr_fd("Philo: pthread_create a échoué\n", 2);
		return (NULL);
	}
	while (1)
	{
		if (boucle_routine_philo(philo) == 1)
			break ;
	}
	pthread_join(thread_ecg, NULL);
	pthread_mutex_destroy(&philo->mange_ou_creve);
	free(philo);
	philo = NULL;
	return (NULL);
}
