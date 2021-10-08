/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 19:50:35 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/08 00:30:28 by jkasongo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"

// zoom pour avoir 50% sur x ou y puis centrage de la map
static void	ft_init_map_placement(t_app *app, t_image *img)
{
	int	big_x;
	int	big_y;
	int	center_x;
	int	center_y;
	int	space_left;

	big_x = W_WIDTH - MENU_WIDTH;
	big_y = W_HEIGHT;
	center_x = 0;
	center_y = 0;
	space_left = 0;
	if ((big_x / app->file_x / 2) > (big_y / app->file_y / 2))
		img->zoom = big_y / app->file_y / 2;
	else
		img->zoom = big_x / app->file_x / 2;
	if (img->zoom < 1)
		img->zoom = 1;
	center_x = ((big_x / 2) + MENU_WIDTH) + space_left;
	center_y = (big_y / 2) + space_left;
	img->map_start_x = center_x - ((app->file_x / 2) * img->zoom);
	img->map_start_y = center_y - ((app->file_y / 2) * img->zoom);
}

static void	ft_get_min_max(t_app *app, t_image *img)
{
	int		x;
	int		y;
	t_coord	***map;

	y = 0;
	img->max = -2147483648;
	img->min = 2147483647;
	map = app->map;
	while (y < app->file_y)
	{
		x = 0;
		while (map[y][x]->end == false)
		{
			if (map[y][x]->z > img->max)
				img->max = map[y][x]->z;
			if (map[y][x]->z < img->min)
				img->min = map[y][x]->z;
			x++;
		}
		if (map[y][x]->z > img->max)
			img->max = map[y][x]->z;
		if (map[y][x]->z < img->min)
			img->min = map[y][x]->z;
		y++;
	}
}

bool	ft_init_image(t_app *app)
{
	t_image	*img;

	app->error_code = 7;
	img = 0;
	app->mlx_img = (t_image *)ft_calloc(1, sizeof(t_image));
	if (!app->mlx_img)
		return (false);
	img = app->mlx_img;
	img->img = mlx_new_image(app->mlx, W_WIDTH, W_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel),
			&(img->line_length), &(img->endian));
	if (!img->img || !img->addr)
		return (false);
	img->palette = 1;
	img->projection = 1;
	ft_get_min_max(app, img);
	ft_init_map_placement(app, img);
	return (true);
}

void	draw_background(t_image *img)
{
	size_t	offset;
	char	*pixel;
	size_t	x;
	size_t	y;

	y = 0;
	ft_bzero(img->addr, W_WIDTH * W_HEIGHT * (img->bits_per_pixel / 8));
	while (y < W_HEIGHT)
	{
		x = 0;
		while (x < W_WIDTH)
		{
			offset = (y * img->line_length) + x * (img->bits_per_pixel / 8);
			pixel = img->addr + offset;
			if (x < MENU_WIDTH)
				*(unsigned int *)pixel = MENU_BACKGROUND;
			else
				*(unsigned int *)pixel = BACKGROUND;
			x++;
		}
		y++;
	}
}

bool	draw_menu(t_app *app)
{
	int		y;
	void	*mlx;
	void	*win;

	y = 0;
	mlx = app->mlx;
	win = app->window;
	mlx_string_put(mlx, win, 50, y += 20, WHITE, "Fil de Fer (FDF)");
	mlx_string_put(mlx, win, 65, y += 30, WHITE, "INSTRUCTIONS");
	mlx_string_put(mlx, win, 65, y += 8, WHITE, "------------");
	mlx_string_put(mlx, win, 15, y += 35, TEXT_COLOR, "Change Palette: C");
	mlx_string_put(mlx, win, 15, y += 80, TEXT_COLOR, "Zoom: Scroll or +/-");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Move: Arrows");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Flatten: </>");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Rotate: Press & Move");
	mlx_string_put(mlx, win, 15, y += 80, WHITE, "Rotate:");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "X-Axis - Key 4 or 6");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Y-Axis - Key 2 or 8");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Z-Axis - Key 1 or 9");
	mlx_string_put(mlx, win, 15, y += 30, WHITE, "Projection");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "ISO: I Key");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Parallel: P Key");
	return (true);
}
