#include "../includes/philosophers.h"

// Init and check of all the structure control data 
// Return 0 in case of success
// Exit properly the program in case of failure 
int   ft_init_struct(t_data *input, int ac, char **av)
{
    if (ac < 5 || ac > 6)
    {
        printf(RED"Error: invalid number of arguments\n"NORMAL);
        exit(EXIT_FAILURE);
    }
    ft_check_input(av);
    input->nb_philos = ft_atoi(av[1]);
    input->time_to_die = ft_atoi(av[2]);
    input->time_to_eat = ft_atoi(av[3]);
    input->time_to_sleep = ft_atoi(av[4]);
    input->must_eat = -1;
    input->is_dead = 0;
    input->stop_eating = 0;
    input->time_to_think = (input->time_to_eat - input->time_to_sleep) * 1000 + 1000;
    if (ac == 6)
        input->must_eat = ft_atoi(av[5]);
    if (input->nb_philos > 200)
        ft_exit("Error: you can't use more than 200 philosophers");
    if (input->nb_philos < 1 || (av[5] && input->must_eat < 1))
            ft_exit("Error: invalid arguments");
    return (0);
}

// Init all the mutex that we will use
int	ft_init_mutex(t_data *input)
{
    int i;

    i = 0;

    input->fork = malloc((input->nb_philos) * sizeof(pthread_mutex_t));
    if (!input->fork)
        return(-1);
    while (i < input->nb_philos)
    {
        pthread_mutex_init(&input->fork[i], NULL);
        i++;
    }
    pthread_mutex_init(&input->m_eat, NULL);
	pthread_mutex_init(&input->m_print, NULL);
    pthread_mutex_init(&input->m_dead, NULL);
    pthread_mutex_init(&input->m_eat_enough, NULL);
    return(0);
}

// Init each philo of the tab of philos.
// Each philo has one mutex left fork initialized here. 
void    ft_init_philos(t_data *input)
{
    int i; 

    input->philosophers = malloc(sizeof(t_philo) * input->nb_philos);
    if (!input->philosophers)
        ft_exit("error: malloc allocation failed");
    i = 0;
    while (i < input->nb_philos)
    {
        input->philosophers[i].time = 0;
        input->philosophers[i].id = i + 1;
        input->philosophers[i].start_time = ft_get_timestamp(); 
        input->philosophers[i].nb_of_meals = 0;
        input->philosophers[i].input = input;
        input->philosophers[i].enough_meals = 0;
        input->philosophers[i].right_fork = (i + 1) % input->nb_philos;
        input->philosophers[i].left_fork = i;
        /*pthread_mutex_init(&input->philosophers[i].left_fork, NULL);
		if (i == input->nb_philos - 1)
			input->philosophers[i].right_fork= &input->philosophers[0].left_fork;
		else
			input->philosophers[i].right_fork = &input->philosophers[i + 1].left_fork;*/
        i++;
    }
    ft_create_threads(input);
}