#include "../includes/philosophers.h"

// Check if the variable enough_meals was set to 1 for all philos
// it would mean that all philos had enough meals
// if all philos had enough meals the variable stop_eating is set to 1
int	ft_eat_enough(t_philo *one_philo)
{
	int	i;
	int	count;

	count = 0;
	pthread_mutex_lock(&one_philo->input->m_eat_enough);
	i = 0;
	while (i < one_philo->input->nb_philos)
	{
		if (one_philo[i].enough_meals == 1)
			count++;
		i++;
	}
	pthread_mutex_unlock(&one_philo->input->m_eat_enough);
	if (count >= one_philo->input->nb_philos)
	{
		pthread_mutex_lock(&one_philo->input->m_eat);
		one_philo->input->stop_eating = 1;
		pthread_mutex_unlock(&one_philo->input->m_eat);
		return (1);
	}
	return (0);
}

// Check if the variable stop_eating was set to 1 (= enough meals for all philos)
// return 1 if all philos ate enough
// return 0 if not all philos ate enough
int	ft_check_meals(t_philo *one_philo)
{
	pthread_mutex_lock(&one_philo->input->m_eat);
	if (one_philo->input->stop_eating == 1)
	{
		pthread_mutex_unlock(&one_philo->input->m_eat);
		return (1);
	}
	pthread_mutex_unlock(&one_philo->input->m_eat);
	return (0);
}

// Check if 
// if all philos had enough meals the variable stop_eating is set to 1
int	ft_is_dead(t_data *input)
{
	int	i;
	
	i = -1;
	while (++i < input->nb_philos)
	{	
		pthread_mutex_lock(&input->m_eat);
		if (input->time_to_die < 
            (ft_get_timestamp() - input->philosophers[i].time)
           // ft_time_diff(input->philosophers[i].time, ft_get_timestamp())
			&& input->philosophers[i].time != 0)
		{
			pthread_mutex_unlock(&input->m_eat);
			ft_print_state(input->philosophers, DIED);
			pthread_mutex_lock(&input->m_dead);
			input->is_dead = 1;
			pthread_mutex_unlock(&input->m_dead);
			return (1);
		}
		else
			pthread_mutex_unlock(&input->m_eat);
	}
	return (0);
}

// Check if the variable is_dead was set to 1 (= one philo died)
// return 1 if one philo died
// return 0 if no one is dead
int	ft_check_death(t_philo *one_philo)
{
	pthread_mutex_lock(&one_philo->input->m_dead);
	if (one_philo->input->is_dead == 1)
	{
		pthread_mutex_unlock(&one_philo->input->m_dead);
		return (1);
	}
	pthread_mutex_unlock(&one_philo->input->m_dead);
	return (0);
}
