#include "../includes/philosophers.h"

void    ft_exit(char *msg)
{
  printf(RED"%s\n"NORMAL, msg);
  exit(EXIT_FAILURE);
}
