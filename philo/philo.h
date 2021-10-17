#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_table
{
	pthread_mutex_t	*forks;
	pthread_mutex_t	stylo;
}	t_table;

typedef struct s_data
{
	int	nb_philo;
	int	t_mourir;
	int	t_manger;
	int	t_dormir;
	int	nb_repas_max;
}	t_data;

typedef struct s_philo_copiste
{
	int		num;
	int		temps;
	t_table	*table;
	int		action;
}	t_philo_copiste;

typedef struct s_philo
{
	int				num;
	int				depart;
	int				mains[2];
	int				t_dernier_repas;
	int				nb_repas;
	int				*mort;
	pthread_mutex_t	*fin;
	pthread_mutex_t	mange_ou_creve;
	t_table			*table;
	t_data			*data;
}	t_philo;

int		ft_strlen(const char *str);
int		ft_atoi(const char *s);
int		ft_isdigit(int c);
void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);

void	check_args(int ac, char ***av);
void	fill_args(char ***args_info, t_data *data);
void	preparer_table(int nb, t_table *table);
int		prendre_forks(t_philo *philo, t_table *table, int nb_philo);
void	lacher_forks(t_philo *philo, t_table *table);
int		manger(t_philo *philo, int t_manger);
int		mtn(void);
int		philo_copiste(t_philo *philo, int num, int temps, int action);
