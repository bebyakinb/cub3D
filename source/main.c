/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 17:31:32 by enoelia           #+#    #+#             */
/*   Updated: 2021/06/30 17:48:39 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	skip_empty_lines(t_list **line)
{
	while ((*line) && ((char *)(*line)->content)[0] == '\0')
		*line = (*line)->next;
}

t_list	*read_file(char *map_file, int reading)
{
	int		fd;
	char	*line;
	t_list	*file;
	t_list	*tmp;

	file = NULL;
	if ((fd = open(map_file, O_RDONLY)) == -1)
		exit_error(2, NULL);
	while ((reading = get_next_line(fd, &line)) > 0)
	{
		if (reading == -1 || !(tmp = ft_lstnew(line)))
		{
			ft_lstclear(&file, free);
			exit_error(-1, NULL);
		}
		ft_lstadd_back(&file, tmp);
	}
	if (!(tmp = ft_lstnew(line)))
	{
		ft_lstclear(&file, free);
		exit_error(-1, NULL);
	}
	ft_lstadd_back(&file, tmp);
	close(fd) == -1 ? exit_error(-1, NULL) : NULL;
	return (file);
}

void	cub3d(char *file, int save_opt)
{
	t_cub		cub;

	init_cub(&cub);
	cub.cub_file = read_file(file, 0);
	parse_cub(&cub);
	check_map(&cub, 0);
	init_angles(&cub);
	if (!(cub.win = mlx_new_window(cub.mlx, cub.screen_x,
									cub.screen_y, "cub3d")))
		exit_error(12, &cub);
	draw_img(&cub, -1);
	if (!save_opt)
	{
		mlx_hook(cub.win, 17, 1L << 17, &ft_exit, &cub);
		mlx_put_image_to_window(cub.mlx, cub.win, cub.img, 0, 0);
		mlx_destroy_image(cub.mlx, cub.img);
		mlx_hook(cub.win, 2, 1L << 0, &draw_screen, &cub);
		mlx_loop(cub.mlx);
	}
	else
	{
		save_bmp(&cub, "screenshot.bmp", cub.screen_x, cub.screen_y);
		mlx_destroy_image(cub.mlx, cub.img);
	}
	ft_exit(&cub);
}

int		main(int argc, char **argv)
{
	if (argc == 2 && check_extension(argv[1], "cub"))
		cub3d(argv[1], 0);
	else if (argc == 3 && check_extension(argv[1], "cub")
			&& !ft_strncmp(argv[2], "--save", 7))
		cub3d(argv[1], 1);
	else
		exit_error(0, NULL);
	return (1);
}
