/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 17:57:00 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/19 18:18:46 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	my_mlx_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= cub->screen_x || y >= cub->screen_y)
		return ;
	dst = cub->addr + (y * cub->line_length + x * (cub->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_vertical_line(t_point start_point,
							int height, t_cub *cub, int color)
{
	while (height)
	{
		my_mlx_pixel_put(cub, start_point.x, start_point.y + height, color);
		height--;
	}
}

void	draw_rectangle(t_cub *cub, t_point start_point,
						t_point end_point, int color)
{
	t_point temp_point;

	temp_point = start_point;
	while (start_point.x < end_point.x)
	{
		start_point.y = temp_point.y;
		while (start_point.y < end_point.y)
		{
			my_mlx_pixel_put(cub, start_point.x, start_point.y, color);
			start_point.y++;
		}
		start_point.x++;
	}
}

void	draw_wall_line_in_3d(int pos, t_wall wall, t_cub *cub)
{
	t_point			pnt;
	unsigned int	color;
	int				t_pos;
	float			texture_hight;
	float			y_pixel_ratio;

	texture_hight = (float)cub->textures[wall.txt_n].height;
	y_pixel_ratio = (float)texture_hight / (float)wall.height;
	if (wall.height >= cub->screen_y)
	{
		texture_hight -= y_pixel_ratio * ((wall.height - cub->screen_y) / 2);
		wall.height = cub->screen_y;
	}
	pnt.x = pos;
	pnt.y = cub->screen_y / 2 - wall.height / 2;
	while (wall.height)
	{
		wall.height--;
		texture_hight -= y_pixel_ratio;
		t_pos = (int)texture_hight * cub->textures[wall.txt_n].len
					+ wall.txt_slice
					* cub->textures[wall.txt_n].bits_per_pixel / 8;\
		if ((color = *(unsigned int *)(cub->textures[wall.txt_n].path + t_pos)))
			my_mlx_pixel_put(cub, pnt.x, pnt.y + wall.height, color);
	}
}

void	draw_sprite_line_in_3d(int pos, int sptr_num, t_cub *cub, t_point pnt)
{
	int		color;
	float	texture_hight;
	float	y_pixel_ratio;
	int		height;

	height = cub->sprts[sptr_num]->end - cub->sprts[sptr_num]->start;
	texture_hight = cub->textures[4].height;
	y_pixel_ratio = (float)texture_hight / (float)height;
	if (height > cub->screen_y)
	{
		texture_hight -= y_pixel_ratio * ((height - cub->screen_y) / 2);
		height = cub->screen_y;
	}
	pnt.x = pos;
	pnt.y = cub->screen_y / 2 - height / 2;
	while (height)
	{
		height--;
		texture_hight -= y_pixel_ratio;
		if ((color = *(unsigned int *)(cub->textures[4].path +
				(int)texture_hight * cub->textures[4].len +
				(int)((pos - cub->sprts[sptr_num]->start) *
				(y_pixel_ratio)) * cub->textures[4].bits_per_pixel / 8)))
			my_mlx_pixel_put(cub, pnt.x, pnt.y + height, color);
	}
}
