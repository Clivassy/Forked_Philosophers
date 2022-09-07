#include "../includes/philosophers.h"

// Terminate the simulation in two cases :
// > Death of one philo : not enough time_to_die 
// > time_each_philos_must_eat is reached
//void	*ft_monitoring(void *arg)
/*void	ft_monitoring(t_philo *one_philo)
{
	//t_philo *one_philo;

	//one_philo = (t_philo*)arg;
	while (1)
	{
		if (ft_is_dead(one_philo->input) == 1)
			//return (NULL);+
			return ;
		if (one_philo->input->must_eat != -1)
			if (ft_eat_enough(one_philo) == 1)
				return ;
				//return (NULL);
		usleep(100);
	}
	//return (NULL);
}*/

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

// While no philos died or have eat enough the simulation goes on. 
void    *ft_live(void *arg)
{
    t_philo *one_philo;

    one_philo = (t_philo*)arg;
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