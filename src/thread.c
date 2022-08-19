#include "../includes/philosophers.h"

void    ft_join_threads(t_data *input)
{
    int i;

    i = 0;
	while (i < input->nb_philos)
	{
		if (pthread_join(input->philosophers[i].thread, NULL))
		{
            free(input->philosophers);// a voir si nécessaire
            ft_exit(input, "Error while joining threads.\n");	
		}
        i++;
	}
}

// Create a thread for each philo
// Quit properly if one creation failed
void    ft_create_threads(t_data *input)
{
    int i;
    pthread_t check_death;

    i = 0;
    while (i < input->nb_philos)
    {
        if (pthread_create(&input->philosophers[i].thread, NULL,
            &ft_live, &input->philosophers[i]))
            {
                free(input->philosophers);// a voir si nécessaire
                ft_exit(input, "Error: thread creation failed");
            }
        i++;
    }
    if (input->nb_philos > 1)
    {
        if (pthread_create(&check_death, NULL, &ft_monitoring, input->philosophers))
            ft_exit(input, "Error: can't create thread");
        pthread_detach(check_death); 
    }
// sinon leaks -> permet de ne pas attendre comme av join.
    ft_join_threads(input);
    //pthread_join(check_death, NULL);
}

void	ft_init_mutex(t_data *input)
{
    pthread_mutex_init(&input->m_eat, NULL);
	pthread_mutex_init(&input->m_print, NULL);
    pthread_mutex_init(&input->m_dead, NULL);
    pthread_mutex_init(&input->m_eat_enough, NULL);
}