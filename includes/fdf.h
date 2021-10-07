#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include "color.h"
# define W_HEIGHT 768
# define W_WIDTH 1366
# define MENU_WIDTH 250

typedef struct s_coord
{
	int		x;
	int		y;
	int		z;
	bool	special;
	bool	end;
	int		color;
}	t_coord;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		bg_color;
	int		menu_bg_color;
	int		palete;
	int		min;
	int		max;
	int		zoom;
	double	alpha;
	double	beta;
	double	gamma;
	int		map_start_x;
	int		map_start_y;
	int		projection;
}	t_image;

typedef struct s_app
{
	void	*mlx;
	void	*window;
	char	*title;
	char	*file_name;
	t_stack	*file_map;
	t_image	*mlx_img;
	int		file_x;
	int		file_y;
	char	*error_message;
	int		error_code;
	int		fd;
	t_coord	***map;
}	t_app;

void	ft_show_error(t_app *app);
void	ft_print_error(char *error_message, int code);
int		openfile(char *filename, t_app *app);
// hooks
int		key_pressed_hook(int key, t_app *app);
int		terminate_hook(t_app *app);

// init mlx image
bool	ft_init_image(t_app *app);
bool	draw_menu(t_app *app);
void	draw_background(t_image *img);
void	ft_draw_fdf(t_app *app);
void	ft_project(t_app *app, t_image *img);
void	ft_rotation_matrix(t_coord *point, t_image *img);
int		ft_get_palete_color(int palete, double percent);
void	project_choice(t_coord *point, t_image *img);
t_coord	prepare_point(t_coord *orignal, t_app *app);

// projections
void	isometric_projection(t_coord *point);

// read file datas and parse into app->file_map stack
bool	read_map_file(t_app *app);
//print file datas collected
void	print_map_file(t_app *app);

// Algorithme de Bresenham
void	draw_segment(t_coord begin, t_coord end, t_image *img);
void	trace_pixel(t_coord *curr, t_coord *end, double percent, t_image *img);

// utils
void	make_title(t_app *app);
t_coord	***make_map(t_app *app);
void	ft_free_map(t_coord ***map, size_t nb_lines);
void	ft_free_file_stack(t_stack *file_map);
#endif
