#include "../includes/philosophers.h"

void    ft_print_state(t_philo *one_philo, char *msg)
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

void ft_sleep(t_philo *one_philo)
{
    ft_print_state(one_philo, SLEEPING);
    ft_usleep(one_philo->input->time_to_sleep);
}

void	ft_leave_forks(t_philo *one_philo)
{
    pthread_mutex_unlock(&one_philo->left_fork);
    pthread_mutex_unlock(one_philo->right_fork);
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
    ft_leave_forks(one_philo);
}

void  ft_take_forks(t_philo *one_philo)
{
    pthread_mutex_lock(&one_philo->left_fork);
    ft_print_state(one_philo, TOOK_FORK);
    if (one_philo->input->nb_philos != 1)
        pthread_mutex_lock(one_philo->right_fork);
    else
        {
            ft_usleep(one_philo->input->time_to_die + 1);
            ft_print_state(one_philo, DIED);
            pthread_mutex_unlock(&one_philo->left_fork);
            pthread_mutex_lock(&one_philo->input->m_dead);
		    one_philo->input->is_dead = 1;
		    pthread_mutex_unlock(&one_philo->input->m_dead);
        }
    ft_print_state(one_philo, TOOK_FORK);
}