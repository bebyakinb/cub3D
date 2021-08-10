/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 19:23:47 by enoelia           #+#    #+#             */
/*   Updated: 2021/06/30 17:46:47 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstadd_back(t_list **lst, t_list *_new)
{
	if (lst && *lst)
		ft_lstlast(*lst)->next = _new;
	else if (lst)
		*lst = _new;
	if (!_new)
		return (0);
	return (1);
}
