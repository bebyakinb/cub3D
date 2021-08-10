/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enoelia <enoelia@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 18:52:59 by enoelia           #+#    #+#             */
/*   Updated: 2021/06/30 17:46:34 by enoelia          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstadd_front(t_list **lst, t_list *_new)
{
	if (!lst || !_new)
		return (0);
	_new->next = *lst;
	*lst = _new;
	return (1);
}
