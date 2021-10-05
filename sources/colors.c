/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 19:30:49 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/04 19:38:48 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

double	ft_percent(int start, int end, int current)
{
	double	dist_2;
	double	distance;

	dist_2 = current - start;
	distance = end - start;
	if (distance == 0)
		return (1.0);
	else
		return (dist_2 / distance);
}

static int	get_r(int trgb)
{
	return (trgb & (0xFF << 16));
}

static int	get_g(int trgb)
{
	return (trgb & (0xFF << 8));
}

static int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

int	ft_gradient(int start, int end, double percent)
{
	int		new[4];

	new[0] = (int)((1 - percent) * get_r(start) + percent * get_r(end));
	new[1] = (int)((1 - percent) * get_g(start) + percent * get_g(end));
	new[2] = (int)((1 - percent) * get_b(start) + percent * get_b(end));
	new[3] = end & (0xFF << 24);
	return (new[3] << 24 | new[0] << 16 | new[1] << 8 | new[2]);
}
