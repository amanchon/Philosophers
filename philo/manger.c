#include "philo.h"

int	prendre_forks(t_philo *philo, t_table *table, int nb_philo)
{
	if (philo->num % 2 == 1)
	{
		if (philo->num == nb_philo)
			pthread_mutex_lock(&table->forks[0]);
		else
			pthread_mutex_lock(&table->forks[philo->num]);
		philo->mains[1] = 1;
		if (philo_copiste(philo, philo->num, mtn() - philo->depart, 1) == 1)
			return (1);
		pthread_mutex_lock(&table->forks[philo->num - 1]);
		philo->mains[0] = 1;
	}
	else
	{
		pthread_mutex_lock(&table->forks[philo->num - 1]);
		philo->mains[0] = 1;
		if (philo_copiste(philo, philo->num, mtn() - philo->depart, 1) == 1)
			return (1);
		if (philo->num == nb_philo)
			pthread_mutex_lock(&table->forks[0]);
		else
			pthread_mutex_lock(&table->forks[philo->num]);
		philo->mains[1] = 1;
	}
	return (0);
}

void	lacher_forks(t_philo *philo, t_table *table)
{
	if (philo->mains[0] == 1)
		pthread_mutex_unlock(&table->forks[philo->num - 1]);
	philo->mains[0] = 0;
	if (philo->mains[1] == 1)
	{
		if (philo->num == philo->data->nb_philo)
			pthread_mutex_unlock(&table->forks[0]);
		else
			pthread_mutex_unlock(&table->forks[philo->num]);
	}
	philo->mains[1] = 0;
}

int	manger(t_philo *philo, int t_manger)
{
	int	t1;
	int	t2;

	t1 = mtn();
	t2 = mtn();
	while (t2 - t1 < t_manger)
	{
		pthread_mutex_lock(philo->fin);
		if (*philo->mort == 1)
		{
			pthread_mutex_unlock(philo->fin);
			return (1);
		}
		pthread_mutex_unlock(philo->fin);
		usleep(100);
		t2 = mtn();
	}
	lacher_forks(philo, philo->table);
	return (0);
}
