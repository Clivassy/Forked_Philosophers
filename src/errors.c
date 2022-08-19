#include "../includes/philosophers.h"

void    ft_exit(t_data *input, char *msg)
{
  int i;

  i = 0;
	if (input->philosophers)
  {
    while (i < input->nb_philos)
      free(&input->philosophers[i]);
    i++;
  }
  printf(RED"%s\n"NORMAL, msg);
  exit(EXIT_FAILURE);
}