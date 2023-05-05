/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbatoro <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/09 14:07:06 by jbatoro           #+#    #+#             */
/*   Updated: 2022/09/09 14:17:10 by jbatoro          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosophers.h"

//-- Return time in millisecond
long long	ft_get_timestamp(void)
{
	struct timeval	current_time;
	long long		timestamp;

	gettimeofday(&current_time, NULL);
	timestamp = current_time.tv_sec * 1000
		+ current_time.tv_usec / 1000;
	return (timestamp);
}

//-- Diff entre sleep et usleep :
// --> usleep accept micro second whereas sleep need second as args.
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
