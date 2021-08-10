/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 12:13:55 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/14 18:50:05 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_color		init_color(void)
{
	t_color	color;

	color.blue = -1;
	color.green = -1;
	color.red = -1;
	return (color);
}

t_sprt		*init_sprite(t_cub *cub, t_point p)
{
	t_sprt	*sprt;

	if (!(sprt = malloc(sizeof(t_sprt))))
		exit_error(-1, cub);
	sprt->x = p.x;
	sprt->y = p.y;
	return (sprt);
}
