/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 19:28:06 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/24 15:46:45 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_txtr_slice_y(t_cub *cub, t_wall *wall, float angle, int x)
{
	int wall_column;

	if (angle >= M_PI)
	{
		wall->txt_n = 0;
		wall_column = x % SCALE;
	}
	else
	{
		wall->txt_n = 1;
		wall_column = SCALE - x % SCALE;
	}
	wall->txt_slice = wall_column
					* (cub->textures[wall->txt_n].width - 1) / SCALE;
	wall->txt_slice = wall->txt_slice % cub->textures[wall->txt_n].width;
}

void	set_txtr_slice_x(t_cub *cub, t_wall *wall, float angle, int x)
{
	int wall_column;

	if (angle >= M_PI / 2 && angle <= 3 * M_PI / 2)
	{
		wall->txt_n = 3;
		wall_column = SCALE - x % SCALE;
	}
	else
	{
		wall->txt_n = 2;
		wall_column = x % SCALE;
	}
	wall->txt_slice = wall_column
					* (cub->textures[wall->txt_n].width - 1) / SCALE;
	wall->txt_slice = wall->txt_slice % cub->textures[wall->txt_n].width;
}

t_wall	get_closest_wall_y(t_cub *cub, float ray_angle)
{
	float		a_x;
	float		a_y;
	float		step_y;
	float		step_x;
	t_wall		wall;

	if (ray_angle >= M_PI)
	{
		a_y = (cub->plr.pos.y / SCALE) * SCALE - 0.1;
		step_y = -SCALE;
		step_x = -SCALE / tan(ray_angle);
	}
	else
	{
		a_y = (cub->plr.pos.y / SCALE) * SCALE + SCALE;
		step_y = SCALE;
		step_x = SCALE / tan(ray_angle);
	}
	a_x = cub->plr.pos.x - (cub->plr.pos.y - a_y) / tan(ray_angle);
	while (is_map_point_correct(cub, set_point(a_x / SCALE, a_y / SCALE)) &&
			cub->map.map_arr[(int)(a_y / SCALE)][(int)(a_x / SCALE)] != '1')
		ft_incrase_position(&a_x, &a_y, step_x, step_y);
	set_txtr_slice_y(cub, &wall, ray_angle, a_x);
	wall.dist = fabs((cub->plr.pos.y - a_y) / sin(ray_angle));
	return (wall);
}

t_wall	get_closest_wall_x(t_cub *cub, float ray_angle)
{
	float		b_x;
	float		b_y;
	float		step_y;
	float		step_x;
	t_wall		wall;

	if (ray_angle >= M_PI / 2 && ray_angle <= 3 * M_PI / 2)
	{
		b_x = (cub->plr.pos.x / SCALE) * SCALE - 0.1;
		step_x = -SCALE;
		step_y = -SCALE * tan(ray_angle);
	}
	else
	{
		b_x = (cub->plr.pos.x / SCALE) * SCALE + SCALE;
		step_x = SCALE;
		step_y = SCALE * tan(ray_angle);
	}
	b_y = cub->plr.pos.y - (cub->plr.pos.x - b_x) * tan(ray_angle);
	while (is_map_point_correct(cub, set_point(b_x / SCALE, b_y / SCALE)) &&
			cub->map.map_arr[(int)(b_y / SCALE)][(int)(b_x / SCALE)] != '1')
		ft_incrase_position(&b_x, &b_y, step_x, step_y);
	set_txtr_slice_x(cub, &wall, ray_angle, b_y);
	wall.dist = fabs((cub->plr.pos.x - b_x) / cos(ray_angle));
	return (wall);
}

t_wall	cast_ray(t_cub *cub, float angle)
{
	t_wall	x_wall;
	t_wall	y_wall;

	x_wall = get_closest_wall_x(cub, correct_angle(angle - M_PI / 8));
	y_wall = get_closest_wall_y(cub, correct_angle(angle - M_PI / 8));
	if (x_wall.dist < y_wall.dist && x_wall.dist != 0)
		return (x_wall.dist < 1 ? y_wall : x_wall);
	return (y_wall.dist < 1 ? x_wall : y_wall);
}
