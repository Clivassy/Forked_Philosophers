#include "../includes/philosophers.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long long int	ft_atoi(const char *nptr)
{
	long long	nb;
	int		i;
	int		signe;

	nb = 0;
	i = 0;
	signe = 1;
	while ((nptr[i] >= 9 && nptr[i] <= 13)
		|| (nptr[i] == 32))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			signe = -signe;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - 48);
		i++;
	}
	return (nb * signe);
}

int ft_syntax_check(char **av)
{
    int i;
    int j;

    i = 1;
    while (av[i])
    {
        j = 0;
        while (av[i][j])
        {
            if (!ft_isdigit(av[i][j]))
			{
				printf(RED"Error: invalid argument\n"NORMAL);
				return(-1);
			}
            j++;
        }
		if (ft_atoi(av[i]) < -2147483648 || ft_atoi(av[i]) > 2147483647)
		{
			printf(RED"Error: invalid argument\n"NORMAL);
			return(-1);
		}
        i++;
    }
    return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

