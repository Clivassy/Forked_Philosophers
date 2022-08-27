#include "../includes/philosophers.h"

void    ft_exit(char *msg)
{
  printf(RED"%s\n"NORMAL, msg);
  exit(EXIT_FAILURE);
}

void    ft_exit_2(t_data *input, char *msg)
{
  printf(RED"%s\n"NORMAL, msg);
  ft_clean(input);
  exit(EXIT_FAILURE);
}