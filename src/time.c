#include "../includes/philosophers.h"

long long	ft_time_diff(long long time_start, long long time_end)
{
	return (time_end - time_start);
}

long long    ft_get_timestamp()
{
	 struct timeval current_time;
    long long timestamp;

    gettimeofday(&current_time, NULL);
	// formule pour calculer le temps en millisecondes
	timestamp = current_time.tv_sec * 1000 
        + current_time.tv_usec / 1000;
	return (timestamp);
}

// diff entre sleep et usleep :
// usleep accept miscro second tandis que sleep il faut passer des secondes 
// en parametre.
void	ft_usleep(int ms)
{
	long int	start;
	long int	actual_time;
	long int	end;

	start = ft_get_timestamp();
	end = start + ms;
	while (1)
	{
		actual_time = ft_get_timestamp();
		if (actual_time >= end)
			break ;
		usleep(10);
	}
}