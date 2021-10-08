/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 21:07:39 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/08 00:06:04 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/color.h"
#include <math.h>

void	ft_rotation_matrix(t_coord	*point, t_image *img)
{
	double	x;
	double	y;
	double	z;

	x = (double)point->x;
	y = (double)point->y;
	z = (double)point->z;
	point->y = (int)round((y * cos(img->alpha)) + (z * sin(img->alpha)));
	point->z = (int)round((-y * sin(img->alpha)) + (z * cos(img->alpha)));
	z = (double)point->z;
	point->x = (int)round((x * cos(img->beta)) + (z * sin(img->beta)));
	point->z = (int)round((-x * sin(img->beta)) + (z * cos(img->beta)));
	x = (double)point->x;
	y = (double)point->y;
	point->x = (int)round(x * cos(img->gamma) - y * sin(img->gamma));
	point->y = (int)round(x * sin(img->gamma) + y * cos(img->gamma));
}

int	ft_get_palette_color(int palete, double percent)
{
	if (palete == 1)
		return (palette_one(percent));
	else if (palete == 2)
		return (palette_two(percent));
	else if (palete == 3)
		return (palette_three(percent));
	else if (palete == 4)
		return (palette_four(percent));
	else if (palete == 5)
		return (palette_five(percent));
	else
		return (palette_one(percent));
}

void	isometric_projection(t_coord *point)
{
	double	x;
	double	y;
	double	z;

	x = (double)point->x;
	y = (double)point->y;
	z = (double)point->z;
	point->x = (int)round((x - y) * cos(0.523599));
	point->y = (int)round((-1 * z) +(x + y) * sin(0.523599));
}

void	project_choice(t_coord *point, t_image *img)
{
	if (img->projection == 1)
		isometric_projection(point);
	return ;
}
