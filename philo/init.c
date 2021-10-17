#include "philo.h"

void	preparer_table(int nb, t_table *table)
{
	int		i;

	i = -1;
	table->forks = malloc(sizeof(pthread_mutex_t) * nb);
	if (table->forks == NULL)
		exit(1);
	while (++i < nb)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return ; //error
	}
	if (pthread_mutex_init(&table->stylo, NULL))
		return ; //error
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
		j = -1;
		while (av[0][i][++j] != '\0')
		{
			if (j > 9 || ft_isdigit(av[0][i][j]) == 0)
			{
				ft_putstr_fd("Philo: Arguments numériques nécessaires !\n", 2);
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
		if (i == 1)
			data->nb_philo = ft_atoi(args_info[0][i]);
		else if (i == 2)
			data->t_mourir = ft_atoi(args_info[0][i]);
		else if (i == 3)
			data->t_manger = ft_atoi(args_info[0][i]);
		else if (i == 4)
			data->t_dormir = ft_atoi(args_info[0][i]);
		else if (i == 5)
			data->nb_repas_max = ft_atoi(args_info[0][i]);
	}
}
