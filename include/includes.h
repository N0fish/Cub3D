/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algultse <algultse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 11:34:56 by roarslan          #+#    #+#             */
/*   Updated: 2024/11/15 19:43:20 by algultse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include "mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include <math.h>
# include "bonus.h"

# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

//with valgrind
# define MOVE_SPEED 0.0633
# define ROTATION_SPEED 0.0633

//without valgrind
// # define MOVE_SPEED 0.0233
// # define ROTATION_SPEED 0.0233

# define NBR_TEXTURES 4
# define MARGIN 0.1
# define ESC 65307
# define A_KEY 97
# define W_KEY 119
# define D_KEY 100
# define S_KEY 115
# define LEFT 65361
# define RIGHT 65363
# define UP 65362
# define DOWN 65364

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

typedef struct s_data	t_data;

typedef struct s_map
{
	char	**map2d;
	char	*floor;
	char	*ceiling;
	int		size;
	int		max_len;
	char	pl_dir;
	char	*north_wall;
	char	*south_wall;
	char	*east_wall;
	char	*west_wall;
	t_data	*data;
}	t_map;

typedef struct s_game
{
	int		f_color;
	int		c_color;
	int		sizey;
	int		sizex;
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planex;
	double	planey;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	deltadistx;
	double	deltadisty;
	double	sidedistx;
	double	sidedisty;
	int		stepx;
	int		stepy;
	int		mapx;
	int		mapy;
	int		hit;
	int		side;
	double	perpwalldist;
	int		lineheigth;
	int		drawstart;
	int		drawend;
	double	olddirx;
	double	oldplanex;
	double	rot_speed;
	double	wallx;
	int		texx;
	int		texy;
	double	step;
	double	texpos;
	double	*zbuffer;
	t_data	*data;
}	t_game;

typedef struct s_texture
{
	int		x;
	int		y;
	void	*img_ptr;
	char	*img_addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		height;
	int		width;
}	t_texture;

typedef struct s_img
{
	t_texture	*texture[NBR_TEXTURES];
	void		*img_ptr;
	char		*img_addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}	t_img;

typedef struct s_keys
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	left;
	int	right;
}	t_keys;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	t_map		*map;
	t_game		*game;
	t_img		*img;
	t_keys		keys;
	t_sprite	*sprites;
	int			num_sprites;
}	t_data;

//check_map.c
void	check_map(t_map *map, char *file);
int		check_name(char *file);
int		check_file_descriptor(char *file);
void	ft_get_size_malloc(t_map *map);
void	get_map_size(t_map *map, char *file);

//check_map2
void	get_max_len(t_map *map);
void	fill_map_helper(t_map *map, int i, int j, char *new_line);
void	fill_map(t_map *map);
char	*delete_spaces(char *str);

//init
void	player_init(t_data *data);
void	player_init_helper1(double dx, double dy, t_data *data);
void	player_init_helper2(double px, double py, t_data *data);
void	allocate_textures(t_data *data);
void	allocate_structures(t_data *data);


//assest_check
int		is_map_assets(char *line);
void	get_map_images(char	*str, t_map *map);
int		small_image_check(t_map *map);
void	get_assets_info(t_map *map, char *file);
int		check_extension(char *file_name);

//textures_check
int		is_textures(char *line);
void	get_map_textures(char *str, t_map *map);
int		check_rgb(char **rgb);
int		check_rgb_format(char *str, int *color);
int		small_textures_check(t_map *map);
void	get_textures_info(t_map *map, char *file);

//check_2dmap
void	get_2dmap_info(t_map *map, char *file);
void	get_map2d(char *line, t_map *map, int fd);
int		is_valid_char(t_map *map, char **tab, int i, int j);
int		check_valid_chars(char **map, t_map *tmap);
int		is_player(char c);

//check2dmap2
void	small_check_map_error(t_map *map);
int		small_check_map(t_map *map, char *prev_line);
int		is_map_closed(char **map);
int		check_closed(char *str);
int		is_ones_and_spaces(char *str);

//check_around
int		check_around(char **tab, int y, int x, char *charset);
int		check_above(char **tab, int y, int x, char *charset);
int		check_below(char **tab, int y, int x, char *charset);
int		is_charset(char c, char *str);

//get_next_line
char	*get_next_line(int fd);
char	*clean_buffer(char *buffer);
char	*fill_line(char *buffer);
char	*read_file(int fd, char *buffer);
char	*ft_strchr(char *s, int c);
size_t	ft_strlen(const char *str);
char	*ft_strdup(char *str);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_calloc(size_t nmemb, size_t size);

//utils
void	ft_putstr_fd(char *str, int fd);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		tab_size(char **tab);
int		ft_isnum(char *str);
int		ft_atoi(const char *str);
char	*ft_strdup_to_n(char *str);
char	*ft_strcpy(char *dest, char *src);
void	*ft_memset(void *s, int c, size_t n);
int		is_map_assets(char *line);
int		check_file_descriptor(char *file_path);

// free.c
void	free_images(t_map *map);
void	free_tab(char **tab);
void	free_and_exit(t_data *data);
void	free_map_resources(t_map *map);
void	ft_destroy_img(t_data *data);
int		ft_escape(t_data *data);

//ft_split
void	free_mem(char **tofree);
int		ft_countwords(char const *str, char c);
char	*ft_strduplicate(char const *str, char c);
int		todup(char **dest, char const *s, char c);
char	**ft_split(char const *s, char c);

//move
void	move_forward(t_data *data);
void	move_backwards(t_data *data);
void	strafe_left(t_data *data);
void	strafe_right(t_data *data);
void	rotate(t_game *game, int i);

//movement
void	handle_movement(t_data *data);
int		ft_keyrelease(int key, t_data *data);
int		ft_keypress(int key, t_data *data);


//casting
void	cast_rays(t_data *data);
void	calculate_sidedist(t_game *game);
void	ft_dda(t_game *game);
void	get_lines_height(t_game *game);

//draw
int		get_cardinal_dir(t_game *game);
void	draw_ceiling(t_game *game, int x);
void	draw_floor(t_game *game, int x);
void	draw_column(t_game *game, int x);

//xpm to image
void	ft_xpm_to_image(t_data *data);
void	ft_xpm_error(t_data *data);
void	ft_get_addr(t_data *data);

#endif