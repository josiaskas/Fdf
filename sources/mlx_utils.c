/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkasongo <jkasongo@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/03 19:50:35 by jkasongo          #+#    #+#             */
/*   Updated: 2021/10/07 02:52:44 by jkasongo         ###   ########.fr       */
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
	img->bg_color = BACKGROUND;
	img->menu_bg_color = MENU_BACKGROUND;
	img->palete = 1;
	img->projection = 1;
	img->text_color = TEXT_COLOR;
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
				*(unsigned int *)pixel = img->menu_bg_color;
			else
				*(unsigned int *)pixel = img->bg_color;
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
	mlx_string_put(mlx, win, 65, y += 20, WHITE, "How to Use");
	mlx_string_put(mlx, win, 15, y += 35, TEXT_COLOR, "Zoom: Scroll or +/-");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Move: Arrows");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Flatten: </>");
	mlx_string_put(mlx, win, 15, y += 30, TEXT_COLOR, "Rotate: Press & Move");
	mlx_string_put(mlx, win, 15, y += 30, WHITE, "Rotate:");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "X-Axis - Key 2 or 8");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Y-Axis - Key 4 or 8");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Z-Axis - Key 1 or 3");
	mlx_string_put(mlx, win, 15, y += 30, WHITE, "Projection");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "ISO: I Key");
	mlx_string_put(mlx, win, 57, y += 25, TEXT_COLOR, "Parallel: P Key");
	return (true);
}
