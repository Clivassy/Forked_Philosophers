/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbatoro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:02:57 by jbatoro           #+#    #+#             */
/*   Updated: 2022/09/09 14:05:02 by jbatoro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_destroy_mutexes(t_data *input, int nb_th_created)
{
	int	nb_th;
	int i;

	if (nb_th_created > 0)
		nb_th = nb_th_created;
	else
		nb_th = input->nb_philos;
	i = 0;
	while (i < nb_th)
	{
		if (pthread_mutex_destroy(&input->fork[i]) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_destroy(&input->m_eat) != 0)
		return (-1);
	if (pthread_mutex_destroy(&input->m_print) != 0)
		return (-1);
	if (pthread_mutex_destroy(&input->m_dead) != 0)
	{
		return (-1);
	}
	if (pthread_mutex_destroy(&input->m_eat_enough) != 0)
		return (-1);
	return (0);
}

int	ft_join_and_end_threads(t_data *input)
{
	int	i;

	i = 0;
	while (i < input->nb_philos)
	{
		if (pthread_join(input->philosophers[i].thread, NULL) != 0)
		{
			ft_destroy_mutexes(input, 0);
			return (-1);
		}
		i++;
	}
	if (ft_destroy_mutexes(input, 0) != 0)
		return (-1);
	return (0);
}

// Create a thread for each philo
// Create another thread to monitor death only if nb_of_philos > 1 
// Quit properly if one creation failed
int	ft_create_threads(t_data *input)
{
	int	i;

	i = 0;
	while (i < input->nb_philos)
	{
		if (pthread_create(&input->philosophers[i].thread, NULL,
				&ft_live, &input->philosophers[i]))
			{
				ft_destroy_mutexes(input, i);
				return (-1);
			}
		i++;
	}
	ft_monitoring(input);
	if (ft_join_and_end_threads(input) < 0)
		return (-1);
	return (0);
}
