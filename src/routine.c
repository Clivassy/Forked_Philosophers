/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbatoro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:01:18 by jbatoro           #+#    #+#             */
/*   Updated: 2022/09/09 14:02:34 by jbatoro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//-- Terminate the simulation in two cases :
// 1- Death of one philo : not enough time_to_die 
// 2- time_each_philos_must_eat is reached
void	ft_monitoring(t_data *input)
{
	while (1)
	{
		if (ft_is_dead(input) == 1)
			return ;
		if (input->must_eat != -1)
			if (ft_eat_enough(input->philosophers) == 1)
				return ;
		usleep(100);
	}
}

//-- While no philos died or have eat enough the simulation goes on. 
void	*ft_live(void *arg)
{
	t_philo	*one_philo;

	one_philo = (t_philo *)arg;
	if (one_philo->id % 2 == 0)
		usleep(1500);
	while (1)
	{
		if (ft_check_death(one_philo) || ft_check_meals(one_philo))
			break ;
		ft_take_forks(one_philo);
		ft_eat(one_philo);
		ft_sleep(one_philo);
		if (ft_check_death(one_philo) || ft_check_meals(one_philo))
			break ;
		ft_print_state(one_philo, THINKING);
		if (one_philo->input->time_to_sleep < one_philo->input->time_to_eat)
			usleep(one_philo->input->time_to_think);
		else
			usleep(1000);
	}
	return (NULL);
}
