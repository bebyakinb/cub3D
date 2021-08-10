/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_screen_scale.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 15:41:35 by enoelia           #+#    #+#             */
/*   Updated: 2021/06/30 17:53:50 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_screen_scale(char *str, int *scale, int max_scale, int min_scale)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	if (i > 4)
		*scale = max_scale;
	else
	{
		if (!(*scale = ft_atoi(str)))
			return (0);
		if (*scale > max_scale)
			*scale = max_scale;
		if (*scale < min_scale)
			*scale = min_scale;
	}
	return (1);
}

void	parse_screen_scale(t_cub *cub, char **parts, int parts_count)
{
	int	screen_max_x;
	int	screen_max_y;

	if (parts_count != 3)
		exit_error(3, cub);
	mlx_get_screen_size(cub->mlx, &screen_max_x, &screen_max_y);
	if (!set_screen_scale(parts[1], &cub->screen_x, screen_max_x, WIN_MIN_X)
	|| !set_screen_scale(parts[2], &cub->screen_y, screen_max_y, WIN_MIN_Y))
		exit_error(16, cub);
	cub->idents.screen_scale++;
}
