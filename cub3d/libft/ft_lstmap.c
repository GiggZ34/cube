/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 18:32:12 by grivalan          #+#    #+#             */
/*   Updated: 2020/12/09 10:42:57 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*begin;
	t_list	*new_lst;

	if (!lst || !f)
		return (0);
	begin = 0;
	while (lst)
	{
		if (!(new_lst = ft_lstnew((*f)(lst->content))))
		{
			ft_lstclear(&begin, (*del));
			return (0);
		}
		ft_lstadd_back(&begin, new_lst);
		lst = lst->next;
	}
	return (begin);
}
