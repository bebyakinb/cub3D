/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 19:01:43 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/24 15:20:11 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		set_txtr(void *mlx, t_txtr *txtr, char *path)
{
	if (!(txtr->img = mlx_xpm_file_to_image(mlx, path, &txtr->width
											, &txtr->height)))
		return (0);
	if (!(txtr->path = mlx_get_data_addr(txtr->img, &txtr->bits_per_pixel
									, &txtr->len, &txtr->endian)))
		return (0);
	return (1);
}

void	parse_txtr(t_cub *cub, char **parts, int parts_count)
{
	int	texture_num;

	if (parts_count != 2)
		exit_error(4, cub);
	if (!(ft_strncmp(parts[0], "NO", 3)))
		texture_num = 0;
	else if (!(ft_strncmp(parts[0], "SO", 3)))
		texture_num = 1;
	else if (!(ft_strncmp(parts[0], "EA", 3)))
		texture_num = 2;
	else if (!(ft_strncmp(parts[0], "WE", 3)))
		texture_num = 3;
	else if (!(ft_strncmp(parts[0], "S", 2)))
		texture_num = 4;
	else
		return ;
	if (!(set_txtr(cub->mlx, &cub->textures[texture_num], parts[1])))
		exit_error(5, cub);
	cub->idents.textures[texture_num] += 1;
}
