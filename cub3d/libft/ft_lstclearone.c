/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclearone.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 10:10:42 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/25 12:54:58 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclearone(t_list **lst, t_list *element, void (*del)(void*))
{
	t_list	*current;
	t_list	*previous;
	t_list	*next;

	if (!lst || !(*lst) || !element)
		return ;
	previous = NULL;
	current = *lst;
	next = current->next;
	while (current != element)
	{
		previous = current;
		current = next;
		if (next)
			next = current->next;
	}
	if (current == element)
	{
		if (!previous)
			*lst = next;
		else
			previous->next = next;
		del(element->content);
		free(element);
	}
}
