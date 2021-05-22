/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclearone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:10:42 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 13:40:44 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_search_lst(t_list **pre, t_list **now, t_list **next, t_list *el)
{
	*next = (*now)->next;
	while (*now && *now != el)
	{
		*pre = *now;
		*now = *next;
		if (*next)
			*next = (*now)->next;
	}
}

void	ft_lstclearone(t_list **lst, t_list *element, void (*del)(void*))
{
	t_list	*current;
	t_list	*previous;
	t_list	*next;

	if (!lst || !(*lst) || !element)
		return ;
	previous = NULL;
	current = *lst;
	ft_search_lst(&previous, &current, &next, element);
	if (current && current == element)
	{
		if (!previous)
		{
			*lst = next;
			(*lst)->previous = NULL;
		}
		else
		{
			previous->next = next;
			if (next)
				next->previous = previous;
		}
		del(element->content);
		free(element);
	}
}
