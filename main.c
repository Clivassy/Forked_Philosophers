#include "./includes/philosophers.h"

/* ------------------------------------------------------------
1\ Initiatisation de la structure d'arguments + check des arguments
2\ Initialisation de la structure de threads (t_philo)
3\ Création des threads : un thread par philo + un thread pour monitorer la fin de la simulation.
4\ Ce thread gère 1) la mort d'un philo et 2) lorsque chaque philo a assez mangé.
5\ Destruction des mutexs + libération de la mémoire allouée dans data.
---------------------------------------------------------------- */
void	ft_free_data(t_data *input)
{
	free(input->philosophers);
	free(input->fork);
}

int main(int argc, char **argv)
{
    t_data input;
    
    if (ft_init_struct(&input, argc, argv) < 0)
        return(-1);
    ft_init_mutex(&input);
    if (ft_init_philos(&input) < 0)
    {
        ft_free_data(&input);
        return(-1);
    }
   	ft_create_threads(&input);
	ft_free_data(&input);
    return (0);
}