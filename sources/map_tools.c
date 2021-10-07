/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 21:07:39 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/07 02:07:06 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include "../includes/color.h"
#include <math.h>

void	ft_rotation_matrix(t_coord	*point, t_image *img)
{
	int	x;
	int	y;

	y = point->y;
	point->y = (y * cos(img->alpha)) + (point->z * sin(img->alpha));
	point->z = (-y * sin(img->alpha)) + (point->z * cos(img->alpha));
	x = point->x;
	point->x = (x * cos(img->beta)) + (point->z * sin(img->beta));
	point->z = (-x * sin(img->beta)) + (point->z * cos(img->beta));
	x = point->x;
	y = point->y;
	point->x = x * cos(img->gamma) - y * sin(img->gamma);
	point->y = x * sin(img->gamma) + y * cos(img->gamma);
	if (point->z > img->max)
		img->max = point->z;
	if (point->z < img->min)
		img->min = point->z;
}

int	ft_get_palete_color(int palete, double percent)
{
	if (palete == 1)
		return (palete_one(percent));
	else if (palete == 2)
		return (palete_two(percent));
	else if (palete == 3)
		return (palete_three(percent));
	else
		return (palete_one(percent));
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
