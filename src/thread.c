#include "../includes/philosophers.h"

int    ft_join_threads(t_data *input)
{
    int i;

    i = 0;
	while (i < input->nb_philos)
	{
		if (pthread_join(input->philosophers[i].thread, NULL))
            return(-1);
        i++;
	}
    return(0);
}

// Create a thread for each philo
// Create another thread to monitor death only if nb_of_philos > 1 
// Quit properly if one creation failed
int    ft_create_threads(t_data *input)
{
    int i;
    pthread_t check_death;

    i = 0;
    while (i < input->nb_philos)
    {
        if (pthread_create(&input->philosophers[i].thread, NULL,
            &ft_live, &input->philosophers[i]))
            return(-1);
        i++;
    }
    if (input->nb_philos > 1)
    {
        if (pthread_create(&check_death, NULL, &ft_monitoring, input->philosophers))
            return(-1);
        pthread_detach(check_death);
    }
    if (ft_join_threads(input) < 0)
        return(-1);
    ft_clean(input);
    return(0);
}