/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 15:59:11 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/04 09:26:27 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*), int del_content)
{
	t_list *tmp;

	if (lst)
	{
		while (*lst)
		{
			tmp = (*lst)->next;
			if (del_content == 1)
				ft_lstdelone((*lst), (*del));
			(*lst) = tmp;
			tmp = 0;
		}
	}
}
