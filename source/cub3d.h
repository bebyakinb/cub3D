/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 15:52:02 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/18 17:42:57 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# define _USE_MATH_DEFINES
# define WIN_MIN_X 320
# define WIN_MIN_Y 240
# define SCALE 20000
# define W_KEY 119
# define S_KEY 115
# define A_KEY 97
# define D_KEY 100
# define X_SIZE_CONST 1.265
# define LEFT_KEY 65361
# define RIGHT_KEY 65363
# define ESC 53
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include "mlx.h"
# include "libft.h"
# include "stdio.h"//

typedef struct	s_map
{
	int			x_max;
	int			y_max;
	int			scale;
	char		**map_arr;
}				t_map;

typedef struct	s_sprite
{
	int			x;
	int			y;
	int			dist;
	int			start;
	int			end;
}				t_sprt;

typedef struct	s_player
{
	t_point		pos;
	float		angle;
}				t_plr;

typedef struct	s_texture
{
	void		*img;
	char		*path;
	int			bits_per_pixel;
	int			endian;
	int			len;
	int			width;
	int			height;
}				t_txtr;

typedef struct	s_idents
{
	int			screen_scale;
	int			ceiling;
	int			floor;
	int			textures[5];
	int			plr;
}				t_idents;

typedef struct	s_color
{
	int			red;
	int			green;
	int			blue;
}				t_color;

typedef struct	s_wall
{
	int			dist;
	int			height;
	int			txt_slice;
	int			txt_n;
}				t_wall;

typedef struct	s_cub
{
	void		*mlx;
	void		*win;
	void		*img;
	void		*map_img;
	char		*addr;
	int			screen_x;
	int			screen_y;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	float		*angles;
	t_list		*lst_sprts;
	t_sprt		**sprts;
	t_list		*cub_file;
	t_map		map;
	t_plr		plr;
	t_txtr		textures[5];
	t_idents	idents;
	t_color		ceiling;
	t_color		floor;
}				t_cub;

/*
** sprites.c
*/
float			ft_getdist_to_sprite(t_sprt p1, t_point p2);
void			set_spirtes_dist(t_cub *cub);
void			sort_sprites(t_cub *cub);
void			get_sprites_size(t_cub *cub);
void			draw_sprites(t_cub *cub, t_wall wall, int win_column);
/*
** hooks.c
*/
void			key_hooker(int keycode, t_cub *cub);
void			draw_img(t_cub *cub, int keycode);
int				draw_screen(int keycode, t_cub *cub);
/*
** raycasting.c
*/
void			set_txtr_slice_y(t_cub *cub, t_wall *wall, float angle, int x);
void			set_txtr_slice_x(t_cub *cub, t_wall *wall, float angle, int x);
t_wall			get_closest_wall_y(t_cub *cub, float ray_angle);
t_wall			get_closest_wall_x(t_cub *cub, float ray_angle);
t_wall			cast_ray(t_cub *cub, float angle);
/*
** parser.c
*/
int				check_identifiers(t_cub *cub);
void			parse_identifier(t_cub *cub, char *line, int *is_idents_parsed);
void			parse_map(t_cub *cub, t_list **line);
void			skip_empty_lines(t_list **line);
void			parse_cub(t_cub *cub);
/*
** parser_colors.c
*/
int				set_color(t_cub *cub, char *color_str);
void			set_plane_color(t_cub *cub, char plane_type, char **rgb);
void			parse_plane_color(t_cub *cub, char **parts, int parts_count);
/*
** parser_textures.c
*/
int				set_txtr(void *mlx, t_txtr *te, char *path);
void			parse_txtr(t_cub *cub, char **parts, int parts_count);
/*
** parser_screen_scale.c
*/
int				set_screen_scale(char *str, int *scale, int max_scale,
								int min_scale);
void			parse_screen_scale(t_cub *cub, char **parts, int parts_count);
/*
** map_drawer.c
*/
int				color_from_rgb(t_color color);
void			draw_background(t_cub *cub);
void			set_plr_point(t_cub *cub, t_point point, char dir);
t_point			set_point(int x, int y);
void			draw_map(t_cub *cub);
/*
** drawer.c
*/
void			my_mlx_pixel_put(t_cub *cub, int x, int y, int color);
void			draw_vertical_line(t_point start_point, int height,
									t_cub *cub, int color);
void			draw_rectangle(t_cub *cub, t_point start_point,
									t_point end_point, int color);
void			draw_wall_line_in_3d(int pos, t_wall wall, t_cub *cub);
void			draw_sprite_line_in_3d(int pos, int sptr_num,
										t_cub *cub, t_point pnt);
/*
** init1.c
*/
void			init_win(t_cub *cub);
t_idents		init_identifiers_strct(void);
void			init_angles(t_cub *cub);
void			init_planes(t_cub *cub);
void			init_cub(t_cub *cub);
/*
** init2.c
*/
t_color			init_color(void);
t_sprt			*init_sprite(t_cub *cub, t_point p);
/*
** main.c  #4 func MAX
*/
void			skip_empty_lines(t_list **line);
t_list			*read_file(char *map_file, int reading);
int				print_errors(t_cub *cub);
void			cub3d(char *file, int save_opt);
/*
** error_exit.c
*/
void			exit_error(int err, t_cub *cub);
void			extra_exit_errors(int err);
int				ft_exit(t_cub *cub);
void			free_parts(char **parts, int parts_count);
/*
** correction_checker.c
*/
int				is_map_point_correct(t_cub *cub, t_point point);
float			correct_angle(float angle);
int				check_extension(char *name, char *extension);
/*
** map_checker.c
*/
void			check_new_field_pos(t_cub *cub, t_point point);
void			check_neighbors(t_cub *cub, t_point p);
void			check_map_sumbol(t_cub *cub, t_point p, int *chars_in_line);
t_sprt			**tlst_to_sprites(t_cub *cub, t_list *lst_sprts);
void			check_map(t_cub *cub, int map_size);
/*
** bmp.c
*/
unsigned char	write_pixel(t_cub *cub, int y, int x, int offset);
void			save_bmp(t_cub *cub, char *filename, int y_max, int x_max);
void			write_img_data(t_cub *cub, int x_max, int y_max, int fd);
#endif
