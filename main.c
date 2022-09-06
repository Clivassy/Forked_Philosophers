#include "./includes/philosophers.h"

/* ------------------------------------------------------------
1\ Initiatisation de la structure d'arguments + check des arguments
2\ Initialisation de la structure de threads (t_philo)
3\ Création des threads : un thread par philo + un thread pour monitorer la fin de la simulation.
4\ Ce thread gère 1) la mort d'un philo et 2) lorsque chaque philo a assez mangé.
5\ Destruction des mutexs + libération de la mémoire allouée dans data.
---------------------------------------------------------------- */

void	ft_clean(t_data *input)
{
	int	i;

	i = 0;
	while (i < input->nb_philos)
	{
		pthread_mutex_destroy(&input->philosophers[i].left_fork);
		i++;
	}
	pthread_mutex_destroy(&input->m_eat);
    pthread_mutex_destroy(&input->m_print);
	pthread_mutex_destroy(&input->m_dead);
	pthread_mutex_destroy(&input->m_eat_enough);

}

int main(int argc, char **argv)
{
    t_data input;
    
    ft_init_struct(&input, argc, argv);
    ft_init_mutex(&input);
    ft_init_philos(&input);
    if (ft_create_threads(&input) < 0)
		{
			//ft_clean(&input);
			return(-1);
		}
    //ft_clean(&input);
	free(input.philosophers);
    return (0);
}