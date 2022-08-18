#include "../includes/philosophers.h"

//--------------------- TEST ---------------------------//
void    ft_print_structure(t_data *input)
{
    printf("NB OF PHILOS = %d\n", input->nb_philos);
    printf("TIME TO DIE = %d\n", input->time_to_die);
    printf("TIME TO EAT = %d\n", input->time_to_eat);
    printf("TIME TO SLEEP = %d\n", input->time_to_sleep);
    printf("TIME EACH PHILO MUST EAT = %d\n", input->must_eat);
}
//----------------------------------------------------//

// Init each philos of the tab of philos.
void    ft_init_philos(t_data *input)
{
    int i; 

	input->philosophers = malloc(sizeof(t_philo) * input->nb_philos);
    if (!input->philosophers)
        ft_exit(input, "error: malloc allocation failed");
    i = 0;
    while (i < input->nb_philos)
    {
        input->philosophers[i].time = 0;
        input->philosophers[i].id = i + 1;
        input->philosophers[i].start_time = ft_get_timestamp(); 
        input->philosophers[i].nb_of_meals = 0;
        input->philosophers[i].input = input;
        input->philosophers[i].enough_meals = 0;
        input->philosophers[i].right_fork = NULL;
        pthread_mutex_init(&input->philosophers[i].left_fork, NULL);
		if (i == input->nb_philos - 1)
			input->philosophers[i].right_fork= &input->philosophers[0].left_fork;
		else
			input->philosophers[i].right_fork = &input->philosophers[i + 1].left_fork;
        i++;
    }
}

// Init and check of all the structure control data 
// Return 0 in case of success
// Exit properly the program in case os failure
// /!\ A voir si il y a d'autres check en plus a faire 
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
    if (input->nb_philos < 1 || input->time_to_die < 1
		|| input->time_to_eat < 1 || input->time_to_sleep < 1
		|| (av[5] && input->must_eat < 1) )
            ft_exit(input, "Error: invalid arguments");
    ft_print_structure(input);
    return (0);
}