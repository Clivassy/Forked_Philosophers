#include "../includes/philosophers.h"

void    ft_exit(t_data *input, char *msg)
{
  (void)input;
	  /*if (input->philosophers)
      free(input->philosophers);*/
    printf("%s\n", msg);
    exit(EXIT_FAILURE);
}

void    ft_exit_2(t_philo *philo)
{
    pthread_mutex_unlock(&philo->input->m_eat);
    ft_clean(philo->input);
    free(philo);
    exit(EXIT_SUCCESS);
}