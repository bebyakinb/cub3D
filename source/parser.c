/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 11:46:34 by enoelia           #+#    #+#             */
/*   Updated: 2021/06/30 17:24:39 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_identifiers(t_cub *cub)
{
	int i;

	if (cub->idents.screen_scale == 0 || cub->idents.ceiling == 0
		|| cub->idents.floor == 0)
		return (0);
	else if (cub->idents.screen_scale > 1 || cub->idents.ceiling > 1
			|| cub->idents.floor > 1)
		exit_error(7, cub);
	i = 0;
	while (i < 5)
	{
		if (cub->idents.textures[i] == 0)
			return (0);
		else if (cub->idents.textures[i] > 1)
			exit_error(7, cub);
		i++;
	}
	return (1);
}

void	parse_identifier(t_cub *cub, char *line, int *is_idents_parsed)
{
	char	**parts;
	int		parts_count;


	if (!line || line[0] == '\0')
		return ;
	if (!(parts = ft_split(line, ' ')))
		exit_error(-1, cub);
	if (line[0] != '\0' && !(parts[0]))
		exit_error(11, cub);
	parts_count = ft_chrarrlen(parts);
	if (parts[0][0] == 'R' && parts[0][1] == '\0'){
		parse_screen_scale(cub, parts, parts_count);}
	else if (ft_strchr("NSWE", parts[0][0]))
		parse_txtr(cub, parts, parts_count);
	else if (((parts[0][0] == 'F' || parts[0][0] == 'C')
				&& parts[0][1] == '\0'))
		parse_plane_color(cub, parts, parts_count);
	else
	{
		free_parts(parts, parts_count);
		*is_idents_parsed = check_identifiers(cub);
		exit_error(11, cub);
	}
	free_parts(parts, parts_count);
	*is_idents_parsed = check_identifiers(cub);
}

void	map_to_tlst(t_cub *cub, t_list **map)
{
	if (!(cub->map.map_arr = ft_tlst_to_chararr(*map)))
	{
		ft_lstclear(map, free);
		exit_error(-1, cub);
	}
	ft_lstclear(map, free);
	if (!(ft_chrarrlen(cub->map.map_arr)))
		exit_error(18, cub);
}

void	parse_map(t_cub *cub, t_list **line)
{
	t_list	*map;
	char	*tmp;

	map = NULL;
	while (*line)
	{
		cub->map.y_max++;
		cub->map.x_max = (int)ft_strlen((char *)(*line)->content)
					> cub->map.x_max ? (int)ft_strlen((char *)(*line)->content) : cub->map.x_max;
		if (!(tmp = ft_strdup((char *)(*line)->content)))
		{
			ft_lstclear(&map, free);
			exit_error(-1, cub);
		}
		if (!ft_lstadd_back(&map, ft_lstnew(tmp)))
		{
			free(tmp);
			ft_lstclear(&map, free);
			exit_error(-1, cub);
		}
		*line = (*line)->next;
	}
	map_to_tlst(cub, &map);
}

void	parse_cub(t_cub *cub)
{
	t_list	*line;
	int		is_idents_parsed;

	is_idents_parsed = 0;
	line = cub->cub_file;
	while (line && !is_idents_parsed)
	{
		parse_identifier(cub, line->content, &is_idents_parsed);
		line = line->next;
	}
	skip_empty_lines(&line);
	if (!is_idents_parsed)
		exit_error(17, cub);
	parse_map(cub, &line);
	ft_lstclear(&cub->cub_file, free);
}
