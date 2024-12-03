/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asalo <asalo@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 10:17:37 by asalo             #+#    #+#             */
/*   Updated: 2024/10/07 10:18:14 by asalo            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "libft/incs/libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>

# define W "\033[0;37m"
# define RB "\033[1;91m"
# define ORANGE "\033[1;93m"
# define GREEN "\33[92m"
# define WB	"\33[1;97m"
# define GREY "\33[90m"
# define RES "\033[0m"

# define WIN_WIDTH 960
# define WIN_HEIGHT 720
# define WIN_NAME "cub3D"
# define FOV 0.66
# define TILE 64
# define PI 3.14159265359
# define BIG_NUM 1e30

/* Textures */
# define TXTR_SIZE 64
# define WEAPON_W 450
# define WEAPON_H 242
# define BYTES_P 4
# define GUN_PATH "./textures/gun.png"

/* MLX Errors */
# define ERROR_PNG "failed to load .png"
# define ERROR_IMG "failed to create mlx image"
# define ERROR_TXTR "failed to add texture to image"
# define ERROR_WINDOW "failed to put mlx image to window\n"
# define ERROR_INIT "failed to initialize mlx"

/* General Errors */
# define ERROR_CUB "unable to open the .cub file"
# define ERROR_GNL "failed while using get next line"
# define ERROR_OPEN "failed to open file"
# define ERROR_ARG "invalid argument count"

/* Map Errors */
# define ERROR_MAP "invalid map"
# define ERROR_WALLS "invalid map play area"
# define ERROR_MISSING_TXTR "invalid or missing texture(s)"
# define ERROR_MAP_NAME "invalid map name"
# define ERROR_MAP_CHAR "invalid map character(s)"
# define ERROR_NO_MAP "no map detected"
# define ERROR_MAP_INFO "invalid map info"
# define ERROR_PLAYER "invalid players count"
# define ERROR_COLOR "invalid color info"

typedef struct s_map
{
	char			**map;
	size_t			size_y;
}					t_map;

typedef struct s_color
{
	unsigned int	b;
	unsigned int	g;
	unsigned int	r;
}					t_color;

typedef struct s_txtr
{
	t_color			*f;
	t_color			*c;
	mlx_texture_t	*n_txtr;
	mlx_texture_t	*e_txtr;
	mlx_texture_t	*s_txtr;
	mlx_texture_t	*w_txtr;
	mlx_texture_t	*gun;
	bool			dup;
	int				txtr_count;
	int				color_count;
}					t_txtr;

typedef struct s_player
{
	double			ppx;
	double			ppy;
	double			pa;
	double			pax;
	double			pay;
	double			plane_x;
	double			plane_y;
	int				is_set;
}					t_player;

typedef struct s_ray
{
	double			camera_x;
	double			dir_x;
	double			dir_y;
	double			d_dist_x;
	double			d_dist_y;
	double			s_dist_x;
	double			s_dist_y;
	double			distance;
	double			wall_height;
	double			wall_x;
	double			text_x;
	double			text_y;
	int				map_x;
	int				map_y;
	int				step_x;
	int				step_y;
	int				hit;
	int				side;
	int				draw_start;
	int				draw_end;
	unsigned char	*pixels;
}					t_ray;

typedef struct s_game
{
	mlx_t			*mlx;
	mlx_image_t		*screen;
	mlx_image_t		*gun;
	t_map			*data;
	t_player		*player;
	t_txtr			*textures;
	t_ray			*ray;
}					t_game;

/* EXTRACT MAP */
int					get_map(char **av, t_game *game);
char				*read_fd(char **av);
/* VALIDATE MAP */
int					get_data(t_game *game);
char				*parse_info(t_game *game, char *line);
mlx_texture_t		*put_png(mlx_texture_t *ptr, char *png, t_game *game);
char				*colors(t_game *game, char *line);
void				str_to_color(t_color *ptr, char *line);
/* MAP INFO */
int					process_data(t_game *game);
int					validate_chars(char **s, t_game *game);
void				set_player(t_game *game, char c, size_t x, size_t y);
int					first_and_last_row(t_map *data);
/* CHECK WALLS */
int					wall_check(t_map *data);
int					handle_spaces(t_map *data);
int					fill(t_map *data, size_t x, size_t y, size_t x_max);
int					fill2(t_map *data, size_t x, size_t y, size_t x_max);
int					edge_rows(t_map *data, size_t x, size_t y);
void				restore(char **map, size_t size_y);
/* MAP UTILS */
int					validate_file(char *name);
int					is_player(char c);
void				invalid_color(t_color *ptr);
int					is_256(t_txtr *t);
void				on_row(int y);
/* GAME */
void				screen(void *param);
void				keys(void *param);
void				get_weapon(t_game *game);
int					gameplay(t_game *game);
void				rotate(t_game *game, int dir);
void				move_up(t_game *game, double speed, double bumber);
void				move_down(t_game *game, double speed, double bumber);
void				move_left(t_game *game, double speed, double bumber);
void				move_right(t_game *game, double speed, double bumber);
void				rotate(t_game *game, int dir);
void				out(t_game *game, char *error);
/* RENDER */
void				raycast(t_game *game);
void				draw(t_game *game, int i);
void				pixel_safe(t_game *game, int x, int y, unsigned int color);
unsigned int		get_color(unsigned char *pixels, int tex_x, int tex_y);
unsigned char		*get_texture_pixels(t_game *game, int i);
/* UTILS */
void				write_err(char *s);
void				free_map(t_game *game);
void				free_arr(char **arr);
char				*gnl_mod(int fd);
char				*strjoin_modi(char *s1, char *s2);
int					atoi_mod(const char *s);
void				out(t_game *game, char *error);

#endif
