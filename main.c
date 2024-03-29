/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbatoro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 13:44:56 by jbatoro           #+#    #+#             */
/*   Updated: 2022/09/09 13:46:36 by jbatoro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/philosophers.h"

void	ft_free_data(t_data *input)
{
	free(input->philosophers);
	free(input->fork);
}

//--	Initiatisation de la structure d'arguments + check des arguments
//--	Initialisation de la structure de threads (t_philo)
//--	Création des threads : un thread par philo 
//--	Création d'un thread pour monitorer la fin de la simulation.
//--   	Ce thread gère 1) la mort d'un philo && 2) lorsque chaque philo a assez mangé.
//--   	Destruction des mutexs + libération de la mémoire allouée dans data.
int	main(int argc, char **argv)
{
	t_data	input;
	int ret;

	if (ft_init_struct(&input, argc, argv) < 0)
		return (-1);
	ret = ft_init_mutex(&input);
	if (ret == -2)
		return (-1);
	if (ret == -1)
	{
		free(input.fork);
		return (-1);
	}
	if (ft_init_philos(&input) < 0)
	{
		ft_free_data(&input);
		return (-1);
	}
	ft_create_threads(&input);
	ft_free_data(&input);
	return (0);
}
