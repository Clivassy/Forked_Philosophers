/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbatoro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 13:52:26 by jbatoro           #+#    #+#             */
/*   Updated: 2022/09/09 13:57:12 by jbatoro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

int	ft_args_check(t_data *input, char **av)
{
	if (input->nb_philos > 200)
	{
		printf(RED"Error: you can't use more than 200 philosophers\n"NORMAL);
		return (-1);
	}
	if (input->nb_philos < 1 || input->time_to_die == 0
		|| (av[5] && input->must_eat == -1))
	{
		printf(RED"Error: invalid arguments\n"NORMAL);
		return (-1);
	}
	return (0);
}

// Init and check of all the structure control data 
// Return 0 in case of success
// Exit properly the program in case of failure 
int	ft_init_struct(t_data *input, int ac, char **av)
{
	if (ac < 5 || ac > 6)
	{
		printf(RED"Error: invalid number of arguments\n"NORMAL);
		return (-1);
	}
	if (ft_syntax_check(av) < 0)
		return (-1);
	input->nb_philos = ft_atoi(av[1]);
	input->time_to_die = ft_atoi(av[2]);
	input->time_to_eat = ft_atoi(av[3]);
	input->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		input->must_eat = ft_atoi(av[5]);
	else
		input->must_eat = -1;
	if (ft_args_check(input, av) < 0)
		return (-1);
	input->is_dead = 0;
	input->stop_eating = 0;
	input->time_to_think = (input->time_to_eat - input->time_to_sleep)
		* 1000 + 1000;
	return (0);
}

// Init all the mutex that we will use
int	ft_init_mutex(t_data *input)
{
	int	i;

	i = 0;
	input->fork = malloc((input->nb_philos) * sizeof(pthread_mutex_t));
	if (!input->fork)
		return (-1);
	while (i < input->nb_philos)
	{
		if (pthread_mutex_init(&input->fork[i], NULL) != 0)
			return (-1);
		i++;
	}
	if (pthread_mutex_init(&input->m_eat, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&input->m_print, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&input->m_dead, NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&input->m_eat_enough, NULL) != 0)
		return (-1);
	return (0);
}

// Init each philo of the tab of philos.
// Each philo has one mutex left fork initialized here. 
int	ft_init_philos(t_data *input)
{
	int	i;

	input->philosophers = malloc(sizeof(t_philo) * input->nb_philos);
	if (!input->philosophers)
	{
		printf("error: malloc allocation failed\n");
		free(input->fork);
		return (-1);
	}
	i = 0;
	while (i < input->nb_philos)
	{
		input->philosophers[i].last_meal = 0;
		input->philosophers[i].id = i + 1;
		input->philosophers[i].start_time = ft_get_timestamp();
		input->philosophers[i].nb_of_meals = 0;
		input->philosophers[i].enough_meals = 0;
		input->philosophers[i].input = input;
		input->philosophers[i].right_fork = (i + 1) % input->nb_philos;
		input->philosophers[i].left_fork = i;
		i++;
	}
	return (0);
}
