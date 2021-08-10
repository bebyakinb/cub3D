/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 18:08:15 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/19 15:55:25 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

unsigned char	write_pixel(t_cub *cub, int y, int x, int offset)
{
	return (unsigned char)(*(unsigned int *)(cub->addr
			+ (y * cub->line_length + x * (cub->bits_per_pixel / 8)
			+ offset)) & 0x000000FF);
}

void			write_img_data(t_cub *cub, int x_max, int y_max, int fd)
{
	int				x;
	unsigned char	*result_img;
	int				y_tmp;
	int				row_len;

	y_tmp = y_max + 1;
	row_len = x_max * 3 + (4 - (x_max * 3) % 4) % 4;
	if (!(result_img = ft_calloc(y_max * row_len, 1)))
		close(fd) == -1 ? exit_error(-1, cub) : exit_error(-1, cub);
	while (--y_tmp > 0)
	{
		x = -1;
		while (++x < x_max)
		{
			result_img[((y_tmp - 1) * row_len)
						+ (x * 3)] = write_pixel(cub, y_max - y_tmp, x, 0);
			result_img[((y_tmp - 1) * row_len)
						+ (x * 3) + 1] = write_pixel(cub, y_max - y_tmp, x, 1);
			result_img[((y_tmp - 1) * row_len)
						+ (x * 3) + 2] = write_pixel(cub, y_max - y_tmp, x, 2);
		}
	}
	write(fd, result_img, y_max * row_len);
	free(result_img);
}

void			save_bmp(t_cub *cub, char *filename, int x_max, int y_max)
{
	int						fd;
	unsigned int			*tmp;
	static unsigned char	header[54] = {66, 77, 0, 0, 0, 0, 0, 0, 0, 0, 54, 0,
						0, 0, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24};

	tmp = (unsigned int*)&header[2];
	*tmp = 54 + y_max * (x_max * 3 + (4 - (x_max * 3) % 4) % 4);
	tmp = (unsigned int*)&header[18];
	*tmp = x_max;
	tmp = (unsigned int*)&header[22];
	*tmp = y_max;
	if ((fd = open(filename, O_WRONLY | O_CREAT, 0777 | O_TRUNC |
							O_APPEND)) == -1)
		exit_error(-1, cub);
	write(fd, header, 54);
	write_img_data(cub, x_max, y_max, fd);
	if ((close(fd)) == -1)
		exit_error(-1, cub);
}
