#include "../includes/philosophers.h"

void	*ft_monitoring(void *arg)
{
	t_philo *one_philo;

	one_philo = (t_philo*)arg;
	while (1)
	{
		if (ft_is_dead(one_philo->input) == 1)
			return (NULL);
		if (one_philo->input->must_eat != -1)
			if (ft_eat_enough(one_philo) == 1)
				return (NULL);
		usleep(100);
	}
	return (NULL);
}

int	ft_is_dead(t_data *input)
{
	int	i;
	
	i = -1;
	while (++i < input->nb_philos)
	{	
		pthread_mutex_lock(&input->m_eat);
		if (input->nb_philos == 1)
		{
			pthread_mutex_unlock(&input->m_eat);
			ft_clean(input);
			free(input->philosophers);
			exit(3);
		}
		if (input->time_to_die < ft_time_diff(input->philosophers[i].time, ft_get_timestamp())
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


/*int	ft_check_end(t_philo *one_philo)
{
	pthread_mutex_lock(&one_philo->input->m_dead);
	pthread_mutex_lock(&one_philo->input->m_eat);
	if (one_philo->input->is_end == 1)
	{
		pthread_mutex_unlock(&one_philo->input->m_dead);
		pthread_mutex_unlock(&one_philo->input->m_eat);
		return (1);
	}
	pthread_mutex_unlock(&one_philo->input->m_dead);
	pthread_mutex_unlock(&one_philo->input->m_eat);
	return (0);
}*/


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
		usleep(1500);
	while (1)
	{
		if (ft_check_death(one_philo) == 1 || ft_check_meals(one_philo) == 1)
			break ;
		ft_take_forks(one_philo);
		//if (ft_check_death(one_philo) == 1 || ft_check_meals(one_philo) == 1)
		//	break ;
		ft_eat(one_philo);
		//if (ft_check_death(one_philo) == 1 || ft_check_meals(one_philo) == 1)
		//	break ;
		ft_sleep(one_philo);
		if (ft_check_death(one_philo) == 1 || ft_check_meals(one_philo) == 1)
			break ;
		ft_print_state(one_philo, THINKING);
		if (one_philo->input->time_to_sleep < one_philo->input->time_to_eat)
			usleep(one_philo->input->time_to_think);
		else
			usleep(1000);
	}
    return (NULL);
}

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