/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:34:07 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/16 01:23:27 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include <math.h>

static int	ft_abs(int n)
{
	if (n >= 0)
		return (n);
	return ((-1) * n);
}

static void	get_sign(int a, int b, int *sign_x, int *sign_y)
{
	int	x;
	int	y;

	x = -1;
	y = -1;
	if (a < 0)
		x = 1;
	if (b < 0)
		y = 1;
	*sign_x = x;
	*sign_y = y;
}

static void	ft_update_error(int sign[], int diff[], int *error, t_coord *curr)
{
	error[1] = error[0] * 2;
	if (error[1] >= diff[1])
	{
		error[0] += diff[1];
		curr->x += sign[0];
	}
	if (error[1] <= diff[0])
	{
		error[0] += diff[0];
		curr->y += sign[1];
	}
}

void	draw_segment(t_coord begin, t_coord end, t_image *img)
{
	t_coord	current;
	int		diff[2];
	int		sign[2];
	int		error[2];
	double	percent;

	diff[0] = ft_abs(end.x - begin.x);
	diff[1] = -ft_abs(end.y - begin.y);
	get_sign((begin.x - end.x), (begin.y - end.y), &sign[0], &sign[1]);
	error[0] = diff[0] + diff[1];
	current = begin;
	percent = 0.0;
	while (current.x != end.x || current.y != end.y)
	{
		trace_pixel(&current, &end, percent, img);
		ft_update_error(sign, diff, &error[0], &current);
		if (diff[0] + diff[1] > 0)
			percent = ft_percent(begin.x, end.x, current.x);
		else
			percent = ft_percent(begin.y, end.y, current.y);
	}
}

void	trace_pixel(t_coord *curr, t_coord *end, double percent, t_image *img)
{
	int		color;
	int		offset;
	char	*pixel;

	color = ft_gradient(curr->color, end->color, percent);
	(void)percent;
	(void)end;
	offset = (curr->y * img->line_length) + curr->x * (img->bits_per_pixel / 8);
	if ((curr->x >= MENU_WIDTH && curr->x < W_WIDTH)
		&& (curr->y >= 0 && curr->y < W_HEIGHT))
	{
		pixel = img->addr + offset;
		*(unsigned int *)pixel = color;
	}
}
