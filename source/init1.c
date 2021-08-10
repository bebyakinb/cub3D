/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init1.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 12:15:29 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/14 18:49:45 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_idents	init_identifiers_strct(void)
{
	t_idents	identifiers;
	int			i;

	identifiers.screen_scale = 0;
	identifiers.ceiling = 0;
	identifiers.floor = 0;
	identifiers.plr = 0;
	i = 0;
	while (i < 5)
	{
		identifiers.textures[i] = 0;
		i++;
	}
	return (identifiers);
}

void		init_angles(t_cub *cub)
{
	int i;

	if (!(cub->angles = malloc(sizeof(float) * cub->screen_x)))
		exit_error(-1, cub);
	i = 0;
	while (i < cub->screen_x)
	{
		(cub->angles)[i] = sin(-M_PI / 8 + i * M_PI / (4 * cub->screen_x));
		i++;
	}
}

void		init_planes(t_cub *cub)
{
	cub->floor = init_color();
	cub->ceiling = init_color();
}

void		init_cub(t_cub *cub)
{
	cub->lst_sprts = NULL;
	cub->map.x_max = 0;
	cub->map.y_max = 0;
	cub->idents = init_identifiers_strct();
	cub->angles = NULL;
	cub->cub_file = NULL;
	init_planes(cub);
	cub->mlx = mlx_init();
}
