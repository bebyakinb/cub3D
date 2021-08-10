/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:59:27 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/23 14:43:26 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_color(t_cub *cub, char *color_str)
{
	int color;

	color = ft_atoi(color_str);
	if (color >= 0 && color <= 255)
		return (color);
	exit_error(6, cub);
	return (-1);
}

void	set_plane_color(t_cub *cub, char plane_type, char **rgb)
{
	t_color	*plane;

	if (plane_type == 'C')
	{
		plane = &cub->ceiling;
		cub->idents.ceiling++;
	}
	else
	{
		plane = &cub->floor;
		cub->idents.floor++;
	}
	plane->red = set_color(cub, rgb[0]);
	plane->green = set_color(cub, rgb[1]);
	plane->blue = set_color(cub, rgb[2]);
}

int		count_commas(char *s)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s && s[i])
	{
		if (s[i] == ',')
			count++;
		i++;
	}
	return (count);
}

void	parse_plane_color(t_cub *cub, char **parts, int parts_count)
{
	char	**rgb;
	int		i;

	if (parts_count != 2)
		exit_error(6, cub);
	i = 0;
	while (parts[1][i])
	{
		if (parts[1][i] != ',' && (!ft_isdigit(parts[1][i])))
			exit_error(6, cub);
		i++;
	}
	if (count_commas(parts[1]) != 2)
		exit_error(6, cub);
	if (!(rgb = ft_split(parts[1], ',')))
		exit_error(-1, cub);
	if (ft_chrarrlen(rgb) != 3)
		exit_error(6, cub);
	set_plane_color(cub, parts[0][0], rgb);
	free_parts(rgb, ft_chrarrlen(rgb));
}
