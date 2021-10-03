/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:34:07 by jkasongo          #+#    #+#             */
/*   Updated: 2021/09/26 01:48:45 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

static int	ft_abs(int n)
{
	if (n >= 0)
		return (n);
	return ((-1) * n);
}

void	draw_segment(t_coord begin, t_coord end)
{
	if ((end.x - begin.x) != 0)
	{
		if ((end.y - begin.y) == 0)
			draw_horizontal_segment(begin, end, end.color);
		else if (ft_abs(end.y - begin.y) < ft_abs(end.x - begin.x))
		{
			if (begin.x > end.x)
				draw_segment_low(begin, end, end.color);
			else
				draw_segment_low(begin, end, end.color);
		}
		else
		{
			if (begin.y > end.y)
				draw_segment_high(begin, end, end.color);
			else
				draw_segment_high(begin, end, end.color);
		}
	}
	else
		draw_vertical_segment(begin, end, end.color);
}

void	trace_pixel(int x, int y, int color)
{
	(void)x;
	(void)y;
	(void)color;
}
