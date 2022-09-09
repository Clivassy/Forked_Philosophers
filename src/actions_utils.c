/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbatoro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 13:50:21 by jbatoro           #+#    #+#             */
/*   Updated: 2022/09/09 13:51:22 by jbatoro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

void	ft_one_philo(t_philo *one_philo)
{
	ft_usleep(one_philo->input->time_to_die + 1);
	ft_print_state(one_philo, DIED);
	pthread_mutex_unlock(&one_philo->input->fork[one_philo->left_fork]);
	pthread_mutex_lock(&one_philo->input->m_dead);
	one_philo->input->is_dead = 1;
	pthread_mutex_unlock(&one_philo->input->m_dead);
}

void	ft_pair_takes_forks(t_philo *one_philo)
{
	pthread_mutex_lock(&one_philo->input->fork[one_philo->right_fork]);
	ft_print_state(one_philo, TOOK_FORK);
	pthread_mutex_lock(&one_philo->input->fork[one_philo->left_fork]);
	ft_print_state(one_philo, TOOK_FORK);
}

void	ft_print_state(t_philo *one_philo, char *msg)
{
	long int	time;

	time = ft_get_timestamp() - one_philo->start_time;
	pthread_mutex_lock(&one_philo->input->m_print);
	pthread_mutex_lock(&one_philo->input->m_dead);
	pthread_mutex_lock(&one_philo->input->m_eat);
	if (one_philo->input->is_dead == 0)
	{
		pthread_mutex_unlock(&one_philo->input->m_dead);
		printf("%ld %d %s\n", time, one_philo->id, msg);
	}
	else
		pthread_mutex_unlock(&one_philo->input->m_dead);
	pthread_mutex_unlock(&one_philo->input->m_eat);
	pthread_mutex_unlock(&one_philo->input->m_print);
}
