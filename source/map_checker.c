/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 17:53:49 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/18 16:41:52 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_new_field_pos(t_cub *cub, t_point point)
{
	int	new_x;
	int	new_y;

	new_x = cub->plr.pos.x + point.x;
	if (cub->map.map_arr[cub->plr.pos.y / SCALE]
						[(new_x - SCALE / 200) / SCALE] != '1'
		&& cub->map.map_arr[cub->plr.pos.y / SCALE]
						[(new_x + SCALE / 200) / SCALE] != '1')
		cub->plr.pos.x = new_x;
	new_y = cub->plr.pos.y + point.y;
	if (cub->map.map_arr[(new_y - SCALE / 200) / SCALE]
						[cub->plr.pos.x / SCALE] != '1'
		&& cub->map.map_arr[(new_y + SCALE / 200) / SCALE]
							[cub->plr.pos.x / SCALE] != '1')
		cub->plr.pos.y = new_y;
}

void	check_neighbors(t_cub *cub, t_point p)
{
	char **arr;

	arr = cub->map.map_arr;
	if (p.x == 0 || arr[p.y][p.x - 1] == ' ' || arr[p.y][p.x + 1] == ' '
		|| arr[p.y][p.x + 1] == '\0' || p.y == 0 || p.y == cub->map.y_max - 1
		|| (int)ft_strlen(arr[p.y - 1]) <= p.x || arr[p.y - 1][p.x] == ' '
		|| arr[p.y - 1][p.x] == '\0' || (int)ft_strlen(arr[p.y + 1]) <= p.x
		|| arr[p.y + 1][p.x] == ' ' || arr[p.y + 1][p.x] == '\0')
		exit_error(15, cub);
}

void	check_map_sumbol(t_cub *cub, t_point p, int *chars_in_line)
{
	t_sprt *tmp;

	if (ft_strchr("\0", cub->map.map_arr[p.y][p.x]))
		return ;
	if (ft_strchr("0", cub->map.map_arr[p.y][p.x]))
		check_neighbors(cub, p);
	else if (ft_strchr("2", cub->map.map_arr[p.y][p.x]))
	{
		check_neighbors(cub, p);
		p.x = (p.x + 0.5) * SCALE;
		p.y = (p.y + 0.5) * SCALE;
		if (!(tmp = init_sprite(cub, p)))
			exit_error(-1, cub);
		if (!(ft_lstadd_back(&cub->lst_sprts, ft_lstnew(tmp))))
			exit_error(-1, cub);
	}
	else if (ft_strchr("NWSE", cub->map.map_arr[p.y][p.x]))
	{
		check_neighbors(cub, p);
		set_plr_point(cub, set_point(p.x * SCALE + SCALE / 2
					, p.y * SCALE + SCALE / 2), cub->map.map_arr[p.y][p.x]);
	}
	*chars_in_line += 1;
}

t_sprt	**tlst_to_sprites(t_cub *cub, t_list *lst_sprts)
{
	t_sprt	**sprites;
	int		size;
	t_list	*tmp;
	t_list	*tmp1;

	tmp = lst_sprts;
	size = ft_lstsize(lst_sprts);
	if (!(sprites = malloc(sizeof(t_sprt*) * (size + 1))))
		exit_error(-1, cub);
	sprites[size] = NULL;
	size--;
	while (tmp)
	{
		tmp1 = tmp;
		sprites[size] = tmp->content;
		tmp = tmp->next;
		free(tmp1);
		tmp1 = NULL;
		size--;
	}
	return (sprites);
}

void	check_map(t_cub *cub, int map_size)
{
	t_point	p;
	int		chars_in_line;

	p.y = 0;
	while (cub->map.map_arr[p.y])
	{
		chars_in_line = 0;
		p.x = 0;
		while (cub->map.map_arr[p.y][p.x])
		{
			if (p.x > cub->map.x_max)
				cub->map.x_max = p.x;
			if (ft_strchr(" 012NWSE\0", cub->map.map_arr[p.y][p.x]))
				check_map_sumbol(cub, p, &chars_in_line);
			else
				exit_error(9, cub);
			map_size++;
			p.x++;
		}
		if (map_size && !chars_in_line)
			exit_error(11, cub);
		p.y++;
	}
	cub->idents.plr ? NULL : exit_error(19, cub);
	cub->sprts = tlst_to_sprites(cub, cub->lst_sprts);
}
