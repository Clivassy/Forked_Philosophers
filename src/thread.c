#include "../includes/philosophers.h"

void    ft_join_threads(t_data *input)
{
    int i;

    i = 0;
	while (i < input->nb_philos)
	{
		if (pthread_join(input->philosophers[i].thread, NULL))
		{
            free(input->philosophers);
            ft_exit_2(input, "Error while joining threads.\n");	
		}
        i++;
	}
}

// Create a thread for each philo
// Create another thread to monitor death only if nb_of_philos > 1 
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
                free(input->philosophers);
                ft_exit_2(input, "Error: thread creation failed");
            }
        i++;
    }
    if (input->nb_philos > 1)
    {
        if (pthread_create(&check_death, NULL, &ft_monitoring, input->philosophers))
            ft_exit_2(input, "Error: can't create thread");
        pthread_detach(check_death);
    }
    ft_join_threads(input);
}