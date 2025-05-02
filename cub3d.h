#ifndef CUB3D_H
# define CUB3D_H

# include "checker/err_mess.h"
# include "minilibx-linux/mlx.h"
# include "utils/getnextline/get_next_line.h"
# include <X11/X.h>      // for X11 keycodes  / CROSS EXIT SHIN
# include <X11/keysym.h> // for keycodes / CROSS EXIT SHIN
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <sys/stat.h>
# include <unistd.h>

# define WIDTH 1366
# define HEIGHT 768
# define NORTH 1
# define SOUTH 2
# define EAST 3
# define WEST 4
# define CUB_SIZE 16
# define W 119
# define A 97
# define S 115
# define D 100
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define ESC 65307
# define PI 3.1415926535

typedef struct s_data
{
	// game
	char	*map;
	char	**game_map;
	void	*north;
	int		heightnorth;
	int		widthnorth;
	void	*south;
	int		heightsouth;
	int		widthsouth;
	void	*east;
	int		heighteast;
	int		widtheast;
	void	*west;
	int		heightwest;
	int		widthwest;
	void	*mlx;
	void	*win;
	int		size_map;
	int		wallX;

	// pixel
	void	*img;
	void	*img_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	int		color_floor;
	int		color_ceilling;

	// joueur
	float	x;
	float	y;
	float	dirX;
	float	dirY;
	float	ddaX;
	float	ddaY;
	float	planeX;
	float	planeY;

	float	angle;

	// keys
	int		w;
	int		s;
	int		a;
	int		d;
	int		left;
	int		right;
}			t_data;

typedef struct s_ray
{
	int		hit;
	int		stepX;
	int		stepY;
	int		x;
	int		y;
	double	deltaDistX;
	double	deltaDistY;
	double	sideDistX;
	double	sideDistY;
	int		side;
	double	dist;

	double	perpWallDist;
}			t_ray;

typedef struct s_tex
{
	int		y;
	int		color;
	double	step;
	double	texPos;
	void	*tex;
	int		texWidth;
	int		texHeight;
	double	lineHeight;
	double	wallX;
	char	*info;
	int		offset;
	int texX; 
	int texY;
	int bpp;
	int line_length; 
	int endian;
}			t_tex;

/* check_map */

int			file_browsing(int fd, t_element *map);
int			check_cub(char *str);
int			check_element(char *file);
void		check_map(t_data *info);

/* check_color_texture */

void		texture(char *line, t_element *map);
int			check_num_color(char *line, int comma, int num, int cont);
int			color(char *line, t_element *map);
void		texture(char *line, t_element *map);

/* init_struct*/

t_element	init_element(void);
t_data		init_list(void);

/* fill_struct */

void		copy_map(int fd, t_data *tex);
void		fill_map(char *file, t_data *tex);
void		fill_texture(char *line, t_data *texture);
void		fill_color(char *line, t_data *texture);

/* fill_struct2 */

void		fill_mlx(t_data *texture);
void		fill_angle(t_data *texture, char lettre);
void		fill_pos(t_data *texture);
int			check_all_fill(t_data *texture);
void		fill_struct(t_data *texture, char *file);

/* utils */

char		*pass_space(char *line);
int			pass_element(t_element *map);
char		*ft_strjoin(char const *s1, char const *s2);
int			len_line(char *map, int i);
int			where_in_line(char *map, int i);
char		**ft_split(char const *s, char c);

/* utils_draw */

void		draw_fov(t_data *game);

/* movement */

int			update(t_data *data);
int			key_release(int keycode, t_data *data);
int			key_press(int keycode, t_data *data);
int			close_handler(t_data *data);

/* draw_game */

void		put_background(t_data *texture);
void		put_minimap(t_data *texture);
void		draw_game(t_data *texture);
void		put_square(t_data *texture, int color, float x, float y);
void		line(t_data *texture, int i);
void		my_mlx_pixel_put(t_data *texture, int x, int y, int color);
void		draw_character(t_data *texture, int radius);

/* ray_casting */

double		dda(t_data *game, t_ray *ray);
void		ray_loop(t_ray *ray, t_data *game);
void		init_ray(t_ray *ray, t_data *game);
void		draw_wall(t_data *game);
int			display_mario_image(void *mlx, void *window);
void		rotate_vector(t_data *texture, float angle_degrees);

int			free_data(t_data *game);
void	draw_texture_line(t_data *texture, t_ray *ray, int x, int drawStart,
        int drawEnd);

#endif