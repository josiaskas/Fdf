#ifndef FDF_H
# define FDF_H

# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# define W_HEIGHT 1080
# define W_WIDTH 1920
# define MENU_WIDTH 250

typedef struct s_coord
{
	int		x;
	int		y;
	int		z;
	bool	special;
	int		color;
}	t_coord;

typedef struct s_app
{
	void	*mlx;
	void	*window;
	char	*title;
	char	*file_name;
	t_stack	*file_map;
	int		file_x;
	int		file_y;
	char	*error_message;
	int		error_code;
	int		fd;
}	t_app;

void	ft_show_error(t_app *app);
void	ft_print_error(char *error_message, int code);
int		openfile(char *filename, t_app *app);
// read file datas and parse into app->file_map stack
bool	read_map_file(t_app *app);

//print file datas collected
void	print_map_file(t_app *app);

// Algorithme général optimisé de Bresenham
void	draw_segment(t_coord begin, t_coord end);
// Ecriture d'un segment horizontal sur y;
void	draw_horizontal_segment(t_coord begin, t_coord end, int color);
// Ecriture d'un segment vertical sur x;
void	draw_vertical_segment(t_coord begin, t_coord end, int color);
void	draw_segment_low(t_coord begin, t_coord end, int color);
void	draw_segment_high(t_coord begin, t_coord end, int color);
void	trace_pixel(int x, int y, int color);

void	make_title(t_app *app);
t_coord	do_nothing(void *point);
t_coord	*map_stack_to_points(t_stack *stack, t_coord (*apply)(void *));
#endif
