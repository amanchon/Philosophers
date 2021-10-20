/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_ecrire.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amanchon <amanchon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 18:45:57 by amanchon          #+#    #+#             */
/*   Updated: 2021/11/20 18:46:38 by amanchon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_mort(t_philo *philo)
{
	int	t_mort;

	t_mort = mtn() - philo->depart;
	*philo->mort = 1;
	pthread_mutex_unlock(&philo->table->fin);
	pthread_mutex_unlock(&philo->mange_ou_creve);
	pthread_mutex_lock(&philo->table->stylo);
	ft_putnbr_fd(t_mort, 1);
	ft_putstr_fd(" Philo ", 1);
	ft_putnbr_fd(philo->num, 1);
	ft_putstr_fd(" died\n", 1);
	pthread_mutex_unlock(&philo->table->stylo);
}

int	philo_copiste(t_philo *philo, int num, int temps, int action)
{
	pthread_mutex_lock(&philo->table->stylo);
	pthread_mutex_lock(&philo->table->fin);
	if (*philo->mort == 1)
	{
		pthread_mutex_unlock(&philo->table->fin);
		pthread_mutex_unlock(&philo->table->stylo);
		return (1);
	}
	pthread_mutex_unlock(&philo->table->fin);
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
