/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 18:31:42 by jkasongo          #+#    #+#             */
/*   Updated: 2021/09/26 01:45:54 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

void	draw_segment_low(t_coord begin, t_coord end, int color)
{
	int	dx;
	int	dy;
	int	e;
	int	sign;

	dx = end.x - begin.x;
	dy = end.y - begin.y;
	sign = 1;
	if (dy < 0)
		sign = -1;
	dy = sign * dy;
	e = (2 * dy) - dx;
	while (begin.x <= end.x)
	{
		trace_pixel(begin.x, begin.y, color);
		if (e > 0)
		{
			begin.y = begin.y + sign;
			e = e + (2 * (dy - dx));
		}
		else
			e = e + (2 * dy);
		begin.x++;
	}
}

void	draw_segment_high(t_coord begin, t_coord end, int color)
{
	int	dx;
	int	dy;
	int	e;
	int	sign;

	dx = end.x - begin.x;
	dy = end.y - begin.y;
	sign = 1;
	if (dx < 0)
		sign = -1;
	dy = sign * dx;
	e = (2 * dy) - dx;
	while (begin.y <= end.y)
	{
		trace_pixel(begin.x, begin.y, color);
		if (e > 0)
		{
			begin.x = begin.x + sign;
			e = e + (2 * (dx - dy));
		}
		else
			e = e + (2 * dx);
		begin.y++;
	}
}

void	draw_horizontal_segment(t_coord begin, t_coord end, int color)
{
	int	dx;

	dx = end.x - begin.x;
	if (dx != 0)
	{
		if (dx > 0)
		{
			while (begin.x <= end.x)
			{
				trace_pixel(begin.x, begin.y, color);
				begin.x++;
			}
		}
		else
		{
			while (begin.x <= end.x)
			{
				trace_pixel(begin.x, begin.y, color);
				begin.x--;
			}
		}
	}
}

void	draw_vertical_segment(t_coord begin, t_coord end, int color)
{
	int	dy;

	dy = end.y - begin.y;
	if (dy != 0)
	{
		if (dy > 0)
		{
			while (begin.y != end.y)
			{
				trace_pixel(begin.x, begin.y, color);
				begin.y++;
			}
		}
		else
		{
			while (begin.y != end.y)
			{
				trace_pixel(begin.x, begin.y, color);
				begin.y--;
			}
		}
	}
}
