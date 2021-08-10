/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 12:39:49 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/14 18:48:54 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	key_hooker(int keycode, t_cub *cub)
{
	if (keycode == W_KEY)
		check_new_field_pos(cub, set_point(SCALE / 3 * cos(cub->plr.angle)
										, SCALE / 3 * sin(cub->plr.angle)));
	else if (keycode == S_KEY)
		check_new_field_pos(cub, set_point(-SCALE / 3 * cos(cub->plr.angle)
										, -SCALE / 3 * sin(cub->plr.angle)));
	else if (keycode == A_KEY)
		check_new_field_pos(cub, set_point(SCALE / 10 * cos(cub->plr.angle
										- M_PI / 2), SCALE / 10
										* sin(cub->plr.angle - M_PI / 2)));
	else if (keycode == D_KEY)
		check_new_field_pos(cub, set_point(SCALE / 10 * cos(cub->plr.angle
										+ M_PI / 2), SCALE / 10
										* sin(cub->plr.angle + M_PI / 2)));
	else if (keycode == LEFT_KEY)
		cub->plr.angle = correct_angle(cub->plr.angle - M_PI / 64);
	else if (keycode == RIGHT_KEY)
		cub->plr.angle = correct_angle(cub->plr.angle + M_PI / 64);
	else if (keycode == ESC)
	{
		mlx_destroy_window(cub->mlx, cub->win);
		ft_exit(cub);
	}
}

void	draw_img(t_cub *cub, int keycode)
{
	int		i;
	t_wall	wall;

	if (!(cub->img = mlx_new_image(cub->mlx, cub->screen_x, cub->screen_y)))
		exit_error(13, cub);
	if (!(cub->addr = mlx_get_data_addr(cub->img, &cub->bits_per_pixel
									, &cub->line_length, &cub->endian)))
		exit_error(14, cub);
	draw_background(cub);
	key_hooker(keycode, cub);
	sort_sprites(cub);
	get_sprites_size(cub);
	i = 0;
	while (i < cub->screen_x)
	{
		wall = cast_ray(cub, cub->plr.angle +
						(float)i * M_PI / (4 * cub->screen_x));
		wall.height = SCALE * cub->screen_x / (cos(cub->angles[i])
											* wall.dist) * (float)X_SIZE_CONST;
		draw_wall_line_in_3d(i, wall, cub);
		draw_sprites(cub, wall, i);
		i++;
	}
}

int		draw_screen(int keycode, t_cub *cub)
{
	draw_img(cub, keycode);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->img, 0, 0);
	mlx_destroy_image(cub->mlx, cub->img);
	return (1);
}
