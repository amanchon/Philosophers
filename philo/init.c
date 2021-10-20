#include "philo.h"

int	preparer_table(int nb, t_table *table)
{
	int		i;

	i = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * nb);
	if (table->forks == NULL)
	{
		ft_putstr_fd("Philo: malloc a échoué\n", 2);
		return (1);
	}
	while (++i < nb)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
		{
			free(table->forks);
			ft_putstr_fd("Philo: mutex_init a échoué\n", 2);
			return (1);
		}
	}
	if (pthread_mutex_init(&table->stylo, NULL))
	{
		free(table->forks);
		ft_putstr_fd("Philo: mutex_init a échoué\n", 2);
		return (1);
	}
	return (0);
}

void	check_args(int ac, char ***av)
{
	int	i;
	int	j;

	i = 0;
	if (ac < 5 || ac > 6)
	{
		ft_putstr_fd("Philo: Il doit y avoir 4 ou 5 arguments !\n", 2);
		exit(1);
	}
	while (av[0][++i] != NULL)
	{
		j = 0;
		while (av[0][i][j] == '0')
			av[0][i] = av[0][i] + 1;
		j = -1;
		while (av[0][i][++j] != '\0')
		{
			if (j > 9 || ft_isdigit(av[0][i][j]) == 0)
			{
				ft_putstr_fd("Philo: Argument invalide !\n", 2);
				exit(1);
			}
		}
	}
	return ;
}

void	fill_args(char ***args_info, t_data *data)
{
	int		i;

	i = 0;
	data->nb_repas_max = -1;
	while (args_info[0][++i] != NULL)
	{
		if (ft_atoll(args_info[0][i]) > 2147483647
			|| (i != 1 && i != 5 && ft_atoll(args_info[0][i]) < 50))
		{
			ft_putstr_fd("Philo: Argument invalide !\n", 2);
			exit(1);
		}
		if (i == 1)
			data->nb_philo = (int)ft_atoll(args_info[0][i]);
		else if (i == 2)
			data->t_mourir = (int)ft_atoll(args_info[0][i]);
		else if (i == 3)
			data->t_manger = (int)ft_atoll(args_info[0][i]);
		else if (i == 4)
			data->t_dormir = (int)ft_atoll(args_info[0][i]);
		else if (i == 5)
			data->nb_repas_max = (int)ft_atoll(args_info[0][i]);
	}
}

pthread_t	*init_args(int ac, char ***av, t_data *data, t_table *table)
{
	pthread_t		*thread_philo;

	if (pthread_mutex_init(&table->fin, NULL))
	{
		ft_putstr_fd("Philo: mutex_init a échoué\n", 2);
		exit(1);
	}
	check_args(ac, av);
	fill_args(av, data);
	if (data->nb_philo == 1)
	{
		ft_putnbr_fd(data->t_mourir + 1, 1);
		ft_putstr_fd(" Philo 1 died\n", 1);
		exit(0);
	}
	thread_philo = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!thread_philo)
	{
		ft_putstr_fd("Philo: malloc a échoué\n", 2);
		exit(1);
	}
	return (thread_philo);
}

t_philo	*creer_philo(t_table *table, int *mort, t_data *data)
{
	t_philo		*philo;

	philo = (t_philo *)malloc(sizeof(t_philo));
	if (philo == NULL)
	{
		ft_putstr_fd("Philo: malloc a échoué\n", 2);
		free(table->forks);
		return (NULL);
	}
	philo->mains[0] = 0;
	philo->mains[1] = 0;
	philo->mort = mort;
	philo->table = table;
	philo->data = data;
	philo->nb_repas = 0;
	if (pthread_mutex_init(&philo->mange_ou_creve, NULL))
	{
		ft_putstr_fd("Philo: malloc a échoué\n", 2);
		free(philo);
		free(table->forks);
		return (NULL);
	}
	return (philo);
}
