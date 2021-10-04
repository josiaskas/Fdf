/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_segment.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 11:34:07 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/04 06:13:43 by jkasongo         ###   ########.fr       */
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

t_coord	prepare_point(t_coord *orignal, t_app *app)
{
	t_coord	result;
	t_image	*img;
	// int		x;
	// int		y;

	img = app->mlx_img;
	result.x = orignal->x * img->zoom;
	result.y = orignal->y * img->zoom;
	result.z = orignal->z * img->zoom;
	// result.x -= (app->file_x * img->zoom) / 2;
	// result.y -= (app->file_y * img->zoom) / 2;
	result.special = orignal->special;
	result.color = orignal->color;
	result.x += MENU_WIDTH + img->map_start_x;
	result.y += ((app->file_y * img->zoom) / 2) + img->map_start_y;
	// x = result.x;
	// y = result.y;
	// result.y = y * cos(img->alpha) + result.z * sin(img->alpha);
	// result.z = -y * sin(img->alpha) + result.z * cos(img->alpha);
	// result.x = x * cos(img->beta) + result.z * sin(img->beta);
	// result.z = -x * sin(img->beta) + result.z * cos(img->beta);
	// x = result.x;
	// y = result.y;
	// result.x = x * cos(img->beta) - y * sin(img->beta);
	// result.y = -x * sin(img->beta) + y * cos(img->beta);
	return (result);
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

void	draw_segment(t_coord begin, t_coord end, t_image *img)
{
	int		diff[2];
	int		sign[2];
	int		error[2];

	diff[0] = ft_abs(end.x - begin.x);
	diff[1] = -ft_abs(end.y - begin.y);
	get_sign((begin.x - end.x), (begin.y - end.y), &sign[0], &sign[1]);
	error[0] = diff[0] + diff[1];
	while (begin.x != end.x || begin.y != end.y)
	{
		trace_pixel(begin, end, img);
		error[1] = error[0] * 2;
		if (error[1] >= diff[1])
		{
			error[0] += diff[1];
			begin.x += sign[0];
		}
		if (error[1] <= diff[0])
		{
			error[0] += diff[0];
			begin.y += sign[1];
		}
	}
}

void	trace_pixel(t_coord curr, t_coord end, t_image *img)
{
	int		color;
	int		offset;
	char	*pixel;

	if (end.special)
		color = end.color;
	else
		color = img->default_point_color;
	offset = (curr.y * img->line_length) + curr.x * (img->bits_per_pixel / 8);
	if ((curr.x >= MENU_WIDTH && curr.x < W_WIDTH)
		&& (curr.y >= 0 && curr.y < W_HEIGHT))
	{
		pixel = img->addr + offset;
		*(unsigned int *)pixel = color;
	}
}
