/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_planes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:53:07 by grivalan          #+#    #+#             */
/*   Updated: 2021/02/04 16:17:57 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		ft_asort_planes(t_list *lst)
{
	t_list	*next;
	t_list	*tmp;
	t_plane	*obj_current;
	t_plane	*obj_next;

	while (lst)
	{
		obj_current = lst->content;
		next = lst->next;
		while (next)
		{
			obj_next = next->content;
			tmp = next;
			next = next->next;
			if (obj_current->d < obj_next->d)
				ft_lst_swap(lst, tmp);
		}
		lst = lst->next;
	}
}

void		ft_sort_planes(t_list *lst)
{
	t_list	*next;
	t_list	*tmp;
	t_plane	*obj_current;
	t_plane	*obj_next;

	while (lst)
	{
		obj_current = lst->content;
		next = lst->next;
		while (next)
		{
			obj_next = next->content;
			tmp = next;
			next = next->next;
			if (obj_current->d > obj_next->d)
				ft_lst_swap(lst, tmp);
		}
		lst = lst->next;
	}
}
