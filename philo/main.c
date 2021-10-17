
#include "philo.h"

int	philo_copiste(t_philo *philo, int num, int temps, int action)
{
	pthread_mutex_lock(&philo->table->stylo);
	pthread_mutex_lock(philo->fin);
	if (*philo->mort == 1)
	{
		pthread_mutex_unlock(philo->fin);
		pthread_mutex_unlock(&philo->table->stylo);
		return (1);
	}
	pthread_mutex_unlock(philo->fin);
	if (action == 2)
		pthread_mutex_lock(&philo->mange_ou_creve);
	ft_putnbr_fd(temps, 1);
	ft_putstr_fd(" Philo ", 1);
	ft_putnbr_fd(num, 1);
	if (action == 1)
		ft_putstr_fd(" has taken a fork\n", 1);
	else if (action == 2)
		ft_putstr_fd(" is eating\n", 1);
	else if (action == 3)
		ft_putstr_fd(" is sleeping\n", 1);
	else if (action == 4)
		ft_putstr_fd(" is thinking\n", 1);
	pthread_mutex_unlock(&philo->table->stylo);
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
	if (manger(philo, philo->data->t_manger) == 1)
		return (1);
	pthread_mutex_lock(&philo->mange_ou_creve);
	philo->nb_repas += 1;
	if (philo->nb_repas == philo->data->nb_repas_max)
	{
		pthread_mutex_unlock(&philo->mange_ou_creve);
		return (1);
	}
	pthread_mutex_unlock(&philo->mange_ou_creve);
	if (philo_copiste(philo, philo->num, mtn() - depart, 3) == 1)
			return (1);
	usleep(1000 * philo->data->t_dormir);
	if (philo_copiste(philo, philo->num, mtn() - depart, 4) == 1)
			return (1);
	return (0);
}

void	*ecg(void *info)
{
	int		t_mort;
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)info;
	table = philo->table;
	while (1)
	{
		pthread_mutex_lock(philo->fin);
		if (*philo->mort == 1)
		{
			pthread_mutex_unlock(philo->fin);
			return (NULL);
		}
		pthread_mutex_unlock(philo->fin);
		pthread_mutex_lock(&philo->mange_ou_creve);
		t_mort = mtn() - philo->t_dernier_repas;
		if (t_mort > philo->data->t_mourir)
		{
			pthread_mutex_lock(philo->fin);
			t_mort = mtn() - philo->depart;
			*philo->mort = 1;
			pthread_mutex_unlock(philo->fin);
			pthread_mutex_unlock(&philo->mange_ou_creve);
			pthread_mutex_lock(&table->stylo);
			ft_putnbr_fd(t_mort, 1);
			ft_putstr_fd(" Philo ", 1);
			ft_putnbr_fd(philo->num, 1);
			ft_putstr_fd(" died\n", 1);
			pthread_mutex_unlock(&table->stylo);
			return (NULL);
		}
		if (philo->nb_repas == philo->data->nb_repas_max)
		{
			pthread_mutex_unlock(&philo->mange_ou_creve);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->mange_ou_creve);
		usleep(2000);
	}
	return (NULL);
}

void	*vie_dun_philo(void *info)
{
	t_philo		*philo;
	pthread_t	thread_ecg;
	int			fin;

	philo = (t_philo *)info;
	philo->depart = mtn();
	if (pthread_create(&thread_ecg, NULL, ecg, philo))
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(philo->fin);
		if (*philo->mort == 1)
		{
			pthread_mutex_unlock(philo->fin);
			break ;
		}
		pthread_mutex_unlock(philo->fin);
		fin = routine_dun_philo(philo);
		if (fin != 0)
		{
			lacher_forks(philo, philo->table);
			break;
		}
	}
	pthread_join(thread_ecg, NULL);
	pthread_mutex_destroy(&philo->mange_ou_creve);
	free(philo);
	philo = NULL;
	return (NULL);
}

int	start_philo(pthread_t *thread_philo, t_philo *philo, int i)
{
	philo->num = i + 1;
	if (pthread_mutex_init(&philo->mange_ou_creve, NULL))
		return (1);//error
	philo->t_dernier_repas = mtn();
	if (pthread_create(&thread_philo[i], NULL, vie_dun_philo, philo))
		return (1); //error
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

t_philo	*creer_philo(t_table *table, pthread_mutex_t *fin, int *mort,
												t_data *data)
{
	t_philo		*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
		return (NULL);
	philo->mains[0] = 0;
	philo->mains[1] = 0;
	philo->mort = mort;
	philo->table = table;
	philo->data = data;
	philo->nb_repas = 0;
	philo->fin = fin;
	if (pthread_mutex_init(&philo->mange_ou_creve, NULL))
		return (NULL);
	return (philo);
}

int	main(int ac, char **av)
{
	t_data			data;
	t_table			table;
	pthread_t		*thread_philo;
	t_philo			*philo;
	int				i;
	int				mort;
	pthread_mutex_t	fin;

	i = -1;
	mort = 0;
	if (pthread_mutex_init(&fin, NULL))
		return (1);//error
	check_args(ac, &av);
	fill_args(&av, &data);
	thread_philo = malloc(sizeof(pthread_t) * data.nb_philo);
	if (!thread_philo)
		return (1); //error
	preparer_table(data.nb_philo, &table);
	while (++i < data.nb_philo)
	{
		philo = creer_philo(&table, &fin, &mort, &data);
		if (philo == NULL)
			exit(1); //error
		if (start_philo(thread_philo, philo, i) == 1)
			exit(1); //error
	}
	att_philo_et_nettoyer_table(thread_philo, &table, data.nb_philo);
	exit(0);
}
