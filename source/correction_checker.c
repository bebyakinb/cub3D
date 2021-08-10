/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correction_checker.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 17:30:52 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/14 21:57:24 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		is_map_point_correct(t_cub *cub, t_point point)
{
	if (point.x < 0 || point.y < 0
		|| point.x >= cub->map.x_max || point.y >= cub->map.y_max)
		return (0);
	return (1);
}

float	correct_angle(float angle)
{
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	while (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

int		check_extension(char *name, char *extension)
{
	char	**parts;
	int		len;
	int		ext_len;

	if (!(parts = ft_split(name, '.')))
		exit_error(-1, NULL);
	len = ft_chrarrlen(parts);
	ext_len = ft_strlen(extension);
	if (!len || ft_strncmp(parts[len - 1], extension, ext_len + 1)
		|| (len == 1 && !(name[0] == '.' && name[1] == '.')))
	{
		free_parts(parts, len);
		exit_error(1, NULL);
	}
	free_parts(parts, len);
	return (1);
}
