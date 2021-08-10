/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 19:46:18 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/14 19:50:14 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_getdist_to_sprite(t_sprt p1, t_point p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)));
}

void	set_sprites_dist(t_cub *cub)
{
	int i;

	i = 0;
	while (cub->sprts[i])
	{
		cub->sprts[i]->dist = ft_getdist_to_sprite(*cub->sprts[i]
													, cub->plr.pos);
		i++;
	}
}

void	sort_sprites(t_cub *cub)
{
	t_sprt		*tmp;
	int			i;
	int			a;

	set_sprites_dist(cub);
	i = 0;
	while (cub->sprts[i])
	{
		a = 0;
		while (cub->sprts[++a])
		{
			if (cub->sprts[a - 1]->dist < cub->sprts[a]->dist)
			{
				tmp = cub->sprts[a - 1];
				cub->sprts[a - 1] = cub->sprts[a];
				cub->sprts[a] = tmp;
			}
		}
		i++;
	}
}

void	get_sprites_size(t_cub *cub)
{
	int		i;
	float	center;
	float	temp_ang;
	float	tmp;

	i = 0;
	while (cub->sprts[i])
	{
		temp_ang = atan2(cub->sprts[i]->y - cub->plr.pos.y
						, cub->sprts[i]->x - cub->plr.pos.x);
		tmp = (cub->plr.angle - temp_ang);
		if (tmp < -M_PI)
			tmp = cub->plr.angle + (2 * M_PI - temp_ang);
		else if (tmp > M_PI)
			tmp = cub->plr.angle - (2 * M_PI + temp_ang);
		center = cub->screen_x / 2 - tmp * (4 * cub->screen_x) / M_PI;
		if (cub->sprts[i]->dist == 0)
			cub->sprts[i]->dist = 1;
		cub->sprts[i]->start = center - SCALE * cub->screen_x
							/ (2 * cub->sprts[i]->dist) * (float)X_SIZE_CONST;
		cub->sprts[i]->end = center + SCALE * cub->screen_x
							/ (2 * cub->sprts[i]->dist) * (float)X_SIZE_CONST;
		i++;
	}
}

void	draw_sprites(t_cub *cub, t_wall wall, int win_column)
{
	int		i;
	t_point empty_pnt;

	empty_pnt = set_point(0, 0);
	i = 0;
	while (cub->sprts[i])
	{
		if (win_column >= cub->sprts[i]->start
			&& win_column < cub->sprts[i]->end)
		{
			if (wall.dist > cub->sprts[i]->dist)
				draw_sprite_line_in_3d(win_column, i, cub, empty_pnt);
		}
		i++;
	}
}
