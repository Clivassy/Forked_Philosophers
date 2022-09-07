#include "../includes/philosophers.h"

void  ft_take_forks(t_philo *one_philo)
{
    t_data *input;

    input = one_philo->input;
    if (one_philo->id % 2 == 0)
        ft_prioritize(one_philo);
	else
	{
		pthread_mutex_lock(&input->fork[one_philo->left_fork]);
        ft_print_state(one_philo, TOOK_FORK);
		if (one_philo->input->nb_philos == 1)
            ft_one_philo(one_philo);
        else
        {
            pthread_mutex_lock(&input->fork[one_philo->right_fork]);
            ft_print_state(one_philo, TOOK_FORK); 
        }		
	}
}

void   ft_eat(t_philo *one_philo)
{
    ft_print_state(one_philo, EATING);
    pthread_mutex_lock(&one_philo->input->m_eat);
    one_philo->time = ft_get_timestamp();
    one_philo->nb_of_meals++;
    if (one_philo->input->must_eat > 0
		&& one_philo->nb_of_meals >= one_philo->input->must_eat)
	{
		pthread_mutex_lock(&one_philo->input->m_eat_enough);
		one_philo->enough_meals = 1;
		pthread_mutex_unlock(&one_philo->input->m_eat_enough);
	}
    pthread_mutex_unlock(&one_philo->input->m_eat);
    ft_usleep(one_philo->input->time_to_eat);
    if (one_philo->input->nb_philos != 1)
        ft_leave_forks(one_philo);
}

void	ft_leave_forks(t_philo *one_philo)
{
    t_data *input; 
    input = one_philo->input;

    pthread_mutex_unlock(&input->fork[one_philo->right_fork]);
    pthread_mutex_unlock(&input->fork[one_philo->left_fork]);
}

void ft_sleep(t_philo *one_philo)
{
    ft_print_state(one_philo, SLEEPING);
    ft_usleep(one_philo->input->time_to_sleep);
}