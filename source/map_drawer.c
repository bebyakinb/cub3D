/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_drawer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:57:22 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/14 18:58:58 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int			color_from_rgb(t_color color)
{
	int	hex_color;

	hex_color = color.red * 65536;
	hex_color += color.green * 256;
	hex_color += color.blue;
	return (hex_color);
}

void		draw_background(t_cub *cub)
{
	draw_rectangle(cub, set_point(0, 0)
				, set_point(cub->screen_x, cub->screen_y / 2)
				, color_from_rgb(cub->ceiling));
	draw_rectangle(cub, set_point(0, cub->screen_y / 2)
				, set_point(cub->screen_x, cub->screen_y)
				, color_from_rgb(cub->floor));
}

void		set_plr_point(t_cub *cub, t_point point, char dir)
{
	if (cub->idents.plr != 0)
		exit_error(10, cub);
	cub->plr.pos.x = point.x;
	cub->plr.pos.y = point.y;
	if (dir == 'N')
		cub->plr.angle = 3 * M_PI / 2;
	else if (dir == 'W')
		cub->plr.angle = M_PI;
	else if (dir == 'S')
		cub->plr.angle = M_PI / 2;
	else if (dir == 'E')
		cub->plr.angle = 0;
	cub->idents.plr += 1;
}

t_point		set_point(int x, int y)
{
	t_point point;

	point.x = x;
	point.y = y;
	return (point);
}

void		draw_map(t_cub *cub)
{
	int		x;
	int		y;

	y = 0;
	while (cub->map.map_arr[y])
	{
		x = 0;
		while (cub->map.map_arr[y][x])
		{
			if (cub->map.map_arr[y][x] == '1')
				draw_rectangle(cub, set_point(x * SCALE, y * SCALE),
					set_point(x * SCALE + SCALE, y * SCALE + SCALE),
					0x00FFFFFF);
			x++;
		}
		y++;
	}
}
