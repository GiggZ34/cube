/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_planes_to_tab.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 08:57:40 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/26 19:51:27 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_list		**ft_planes_top_to_tab(t_game *game)
{
	int		size;
	t_list	**tab;
	t_list	*list;
	t_plane	*plane;
	int		i;

	size = game->file.height_map;
	if (!(tab = ft_calloc(sizeof(t_plane*), size + 1)))
		return (NULL);
	i = -1;
	while (++i <= size)
		tab[i] = NULL;
	list = game->lst_planes_top;
	while (list)
	{
		plane = list->content;
		tab[(int)ft_abs(plane->d) - 1] = list;
		list = list->next;
	}
	return (tab);
}

static t_list		**ft_planes_bottom_to_tab(t_game *game)
{
	int		size;
	t_list	**tab;
	t_list	*list;
	t_plane	*plane;
	int		i;

	size = game->file.height_map;
	if (!(tab = ft_calloc(sizeof(t_plane*), size + 1)))
		return (NULL);
	i = -1;
	while (++i <= size)
		tab[i] = NULL;
	list = game->lst_planes_bottom;
	while (list)
	{
		plane = list->content;
		tab[(int)plane->d] = list;
		list = list->next;
	}
	return (tab);
}

static t_list		**ft_planes_right_to_tab(t_game *game)
{
	int		size;
	t_list	**tab;
	t_list	*list;
	t_plane	*plane;
	int		i;

	size = game->file.width_map;
	if (!(tab = ft_calloc(sizeof(t_plane*), size + 1)))
		return (NULL);
	i = -1;
	while (++i <= size)
		tab[i] = NULL;
	list = game->lst_planes_right;
	while (list)
	{
		plane = list->content;
		tab[(int)plane->d] = list;
		list = list->next;
	}
	return (tab);
}

static t_list		**ft_planes_left_to_tab(t_game *game)
{
	int		size;
	t_list	**tab;
	t_list	*list;
	t_plane	*plane;
	int		i;

	size = game->file.width_map;
	if (!(tab = ft_calloc(sizeof(t_plane*), size + 1)))
		return (NULL);
	i = -1;
	while (++i <= size)
		tab[i] = NULL;
	list = game->lst_planes_left;
	while (list)
	{
		plane = list->content;
		tab[(int)ft_abs(plane->d) - 1] = list;
		list = list->next;
	}
	return (tab);
}

int					ft_lst_planes_to_tab(t_game *game)
{
	if (!(game->tab_planes.left = ft_planes_left_to_tab(game)))
		return (ft_trash_game(game, allocation_fail, -1, "\n"));
	if (!(game->tab_planes.right = ft_planes_right_to_tab(game)))
		return (ft_trash_game(game, allocation_fail, -1, "\n"));
	if (!(game->tab_planes.top = ft_planes_top_to_tab(game)))
		return (ft_trash_game(game, allocation_fail, -1, "\n"));
	if (!(game->tab_planes.bottom = ft_planes_bottom_to_tab(game)))
		return (ft_trash_game(game, allocation_fail, -1, "\n"));
	return (0);
}
