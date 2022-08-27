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
