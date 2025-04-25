#ifndef CUB3D_H
# define CUB3D_H

# include "getnextline/get_next_line.h"
# include "checker/err_mess.h"
# include "minilibx-linux/mlx.h"

# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>

# define WIDTH		1366
# define HEIGHT		768
# define ANG_NORTH -1
# define ANG_SOUTH 270
# define ANG_EAST 0
# define ANG_WEST 180
# define CUB_SIZE 32
# define W		119
# define A		97
# define S		115
# define D		100
# define UP		65362
# define DOWN	65364
# define LEFT	65361
# define RIGHT	65363
# define ESC	65307
# define PI 	3.1415926535

typedef struct s_data
{

	// game
	char	*map;
	char	**game_map;
	void	*north;
	void	*south;
	void	*east;
	void	*west;
	void	*mlx;
	void	*win;
	int	size_map;

	// pixel
	void	*img;
	void	*img_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	int		color_floor;
	int		color_ceilling;

	//joueur
	float		x;
	float		y;
	float		dirX;
	float		dirY;

	float		angle;

	// keys
	int w;
	int s;
	int a;
	int d;
	int left;
	int right;
}			t_data;

typedef struct s_ray
{
	int	loop;
	int	x;
	int	y;
	float	fx;
	float	fy;
	float	distance;
	float	distance2;
}			t_ray;

                /* check_map */

int file_browsing(int fd, t_element* map);
int	check_cub(char *str);
int check_element(char* file);
void check_map(t_data* info);

                /* check_color_texture */

void texture(char* line, t_element* map);
int check_num_color(char* line, int comma, int num, int cont);
int color(char* line, t_element* map);
void texture(char* line, t_element* map);

                /* init_struct*/

t_element init_element(void);
t_data init_list(void);

                /* fill_struct */

void copy_map(int fd, t_data* tex);               
void fill_map(char* file, t_data* tex);
void fill_texture(char* line, t_data* texture);
void fill_color(char* line, t_data* texture);

				/* fill_struct2 */

void fill_mlx(t_data* texture);
void fill_angle(t_data* texture, char lettre);
void fill_pos(t_data *texture);
int check_all_fill(t_data* texture);
void fill_struct(t_data *texture, char* file);


                /* utils */

char* pass_space(char* line);
int pass_element(t_element* map);
char	*ft_strjoin(char const *s1, char const *s2);
int	len_line(char *map, int i);
int	where_in_line(char *map, int i);
char	**ft_split(char const *s, char c);

		/* movement */

int update(t_data *data);
int key_release(int keycode, t_data *data);
int key_press(int keycode, t_data *data);

		/* draw_game */

void put_background(t_data* texture);
void put_minimap(t_data* texture);
void draw_game(t_data* texture);
void put_square(t_data *texture, int color, int size, float x, float y);
void	line(t_data *texture);
void	my_mlx_pixel_put(t_data *texture, int x, int y, int color);

#endif