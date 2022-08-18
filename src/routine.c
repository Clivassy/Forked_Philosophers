#include "../includes/philosophers.h"

void	*ft_monitoring(void *arg)
{
	t_data *input;
	t_philo *one_philo;

	one_philo = (t_philo*)arg;
	input = one_philo->input;
	while (1)
	{
		if (ft_is_dead(input, one_philo) == 1)
			return (NULL);
		if (input->must_eat != -1)
			if (ft_eat_enough(input, one_philo) == 1)
				return (NULL);
		usleep(100);
	}
	return (NULL);
}

int	ft_is_dead(t_data *input, t_philo *one_philo)
{
	int	i;

	i = 0;
	while (i < input->nb_philos)
	{
		pthread_mutex_lock(&input->m_eat);
		if (input->time_to_die < ft_time_diff(one_philo[i].time, ft_get_timestamp())
			&& one_philo[i].time != 0)
		{
			pthread_mutex_unlock(&input->m_eat);
			ft_print_state(one_philo, DIED);
			pthread_mutex_lock(&input->m_dead);
			input->is_dead = 1;
			pthread_mutex_unlock(&input->m_dead);
			return (1);
		}
		else
			pthread_mutex_unlock(&input->m_eat);
		i++;
	}
	return (0);
}

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

/* Deux cas mettent fin au process de vie des philos:
* > La mort d'un philo : time_to_die insuffisant
* > Le nombre de time_each_philos_must_eat est atteint
*/
void    *ft_live(void *arg)
{
    t_philo *one_philo;

    one_philo = (t_philo*)arg;
	if (one_philo->id % 2 == 0)
		ft_usleep(2);
	while (1)
	{
		if (ft_check_death(one_philo) == 1 || ft_check_meals(one_philo) == 1)
			break ;
		ft_take_forks(one_philo);
		if (ft_check_death(one_philo) == 1 || ft_check_meals(one_philo) == 1)
			break ;
		ft_eat(one_philo);
		if (ft_check_death(one_philo) == 1 || ft_check_meals(one_philo) == 1)
			break ;
		ft_sleep_and_think(one_philo);
		if (one_philo->input->time_to_sleep < one_philo->input->time_to_eat)
			usleep(one_philo->input->time_to_think);
		if (ft_check_death(one_philo) == 1 || ft_check_meals(one_philo) == 1)
			break ;
		ft_print_state(one_philo, THINKING);
	}
    return (NULL);
}

int	ft_eat_enough(t_data *input, t_philo *one_philo)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	pthread_mutex_lock(&input->m_eat_enough);
	while (i < input->nb_philos)
	{
		if (one_philo[i].enough_meals == 1)
			count++;
		i++;
	}
	pthread_mutex_unlock(&one_philo->input->m_eat_enough);
	if (count >= input->nb_philos)
	{
		pthread_mutex_lock(&input->m_eat);
		input->stop_eating = 1;
		pthread_mutex_unlock(&input->m_eat);
		return (1);
	}
	return (0);
}
/*{
	int	i;

	i = 0;
	pthread_mutex_lock(&input->m_eat);
	while (input->must_eat != -1 && i < input->nb_philos
		&& one_philo[i].nb_of_meals >= input->must_eat)
	{
		i++;
	}
	pthread_mutex_unlock(&input->m_eat);
	if (i >= input->nb_philos)
	{
		pthread_mutex_lock(&input->m_eat);
		input->stop_eating = 1;
		pthread_mutex_unlock(&input->m_eat);
	}
	if (input->stop_eating == 1)
	{
		return (1);
	}	
	return (0);
}*/