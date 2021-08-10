/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 18:41:50 by enoelia           #+#    #+#             */
/*   Updated: 2020/10/19 13:55:14 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	exit_error(int err, t_cub *cub)
{
	ft_putstr_fd("Error\n", 2);
	if (err >= 8)
		extra_exit_errors(err);
	if (err == -1)
		ft_putstr_fd("MEMORY ERROR\n", 2);
	else if (err == 0)
		ft_putstr_fd("WRONG ARGUMENTS\n", 2);
	else if (err == 1)
		ft_putstr_fd("NO SUCH FILE OR WRONG EXTENSION\n", 2);
	else if (err == 2)
		ft_putstr_fd("READING ERROR\n", 2);
	else if (err == 3)
		ft_putstr_fd("WRONG SCREEN SIZE\n", 2);
	else if (err == 4)
		ft_putstr_fd("WRONG TEXTURE IDENTIFIER\n", 2);
	else if (err == 5)
		ft_putstr_fd("WRONG IMAGE PATH\n", 2);
	else if (err == 6)
		ft_putstr_fd("WRONG PLANE COLOR INPUT\n", 2);
	else if (err == 7)
		ft_putstr_fd("MORE THAN ONE SAME IDENTIFIER\n", 2);
	if (cub)
		ft_exit(cub);
	exit(0);
}

void	extra_exit_errors(int err)
{
	if (err == 8)
		ft_putstr_fd("MAP ISN'T CLOSED\n", 2);
	else if (err == 9)
		ft_putstr_fd("PROHIBITED SUMBOLS AFTER IDENTIFIER BLOC\n", 2);
	else if (err == 10)
		ft_putstr_fd("MORE THAN ONE PLAYER POINT\n", 2);
	else if (err == 11)
		ft_putstr_fd("UNNECESSARY LINES IN CUB-FILE\n", 2);
	else if (err == 12)
		ft_putstr_fd("MLX CAN'T CREATE WINDOW\n", 2);
	else if (err == 13)
		ft_putstr_fd("MLX CAN'T CREATE IMAGE\n", 2);
	else if (err == 14)
		ft_putstr_fd("MLX CAN'T RETURN IMAGE ADDRES\n", 2);
	else if (err == 15)
		ft_putstr_fd("MAP ISN'T CLOSE\n", 2);
	else if (err == 16)
		ft_putstr_fd("WRONG SCREEN SIZE OR MEMORY ERROR\n", 2);
	else if (err == 17)
		ft_putstr_fd("NOT ENOUGH IDENTIFIERS\n", 2);
	else if (err == 18)
		ft_putstr_fd("NO MAP IN CUB FILE\n", 2);
	else if (err == 19)
		ft_putstr_fd("NO PLAYER ON THE MAP\n", 2);
}

int		ft_exit(t_cub *cub)
{
	if (cub->angles)
		free(cub->angles);
	ft_lstclear(&cub->cub_file, free);
	exit(0);
	return (0);
}

void	free_parts(char **parts, int parts_count)
{
	int i;

	i = 0;
	while (i < parts_count)
	{
		free(parts[i]);
		parts[i] = NULL;
		i++;
	}
	free(parts);
	parts = NULL;
}
