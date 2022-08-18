#include "../includes/philosophers.h"

void    ft_exit(t_data *input, char *msg)
{
  (void)input;
	  /*if (input->philosophers)
      free(input->philosophers);*/
    printf("%s\n", msg);
    exit(EXIT_FAILURE);
}