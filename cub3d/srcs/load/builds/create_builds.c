/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_walls.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:25:25 by grivalan          #+#    #+#             */
/*   Updated: 2021/01/25 17:19:25 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_wall	*ft_init_wall(t_game *game, t_plane *plane, t_dot pos, int *id)
{
	t_wall		*wall;

	pos.z = 1;
	if (!(wall = ft_calloc(sizeof(t_wall), 1)))
		return (0);
	wall->id = *id;
	(*id)++;
	wall->a = plane->a;
	wall->b = plane->b;
	wall->c = plane->c;
	wall->d = plane->d;
	wall->pos = pos;
	wall->height = 1;
	wall->width = 1;
	if (wall->a == 1)
		wall->add = game->file->texture_so;
	else
		wall->add = game->file->texture_ea;
	return (wall);
}

static int		ft_create_around_wall(t_game *game, t_wall *wall)
{
	t_wall	*around_wall[3];
	t_list	*lst;

	if (!(around_wall[0] = ft_calloc(sizeof(t_wall), 1)))
		return (3);
	if (!(around_wall[1] = ft_calloc(sizeof(t_wall), 1)))
	{
		free(around_wall[0]);
		return (3);
	}
	if (!(around_wall[2] = ft_calloc(sizeof(t_wall), 1)))
	{
		free(around_wall[0]);
		free(around_wall[1]);
		return (3);
	}
	if (wall->a == 1)
	{
		around_wall[0]->id = wall->id;
		around_wall[0]->a = 1;
		around_wall[0]->b = 0;
		around_wall[0]->c = 1;
		around_wall[0]->d = wall->d - 1;
		around_wall[0]->height = wall->height;
		around_wall[0]->width = wall->width;
		around_wall[0]->pos.x = wall->pos.x;
		around_wall[0]->pos.y = wall->pos.y + 1;
		around_wall[0]->add = game->file->texture_no;
		around_wall[1]->id = wall->id;
		around_wall[1]->a = 0;
		around_wall[1]->b = 1;
		around_wall[1]->c = 1;
		around_wall[1]->d = -(wall->pos.y);
		around_wall[1]->height = 1;
		around_wall[1]->width = 1;
		around_wall[1]->pos.x = wall->pos.x;
		around_wall[1]->pos.y = wall->pos.y;
		around_wall[1]->add = game->file->texture_we;
		around_wall[2]->id = wall->id;
		around_wall[2]->a = 0;
		around_wall[2]->b = 1;
		around_wall[2]->c = 1;
		around_wall[2]->d = -(wall->pos.y);
		around_wall[2]->height = 1;
		around_wall[2]->width = 1;
		around_wall[2]->pos.x = wall->pos.x + wall->width - 1;
		around_wall[2]->pos.y = wall->pos.y;
		around_wall[2]->add = game->file->texture_ea;
	}
	if (wall->b == 1)
	{
		around_wall[0]->id = wall->id;
		around_wall[0]->a = 0;
		around_wall[0]->b = 1;
		around_wall[0]->c = 1;
		around_wall[0]->d = wall->d - 1;
		around_wall[0]->height = wall->height;
		around_wall[0]->width = wall->width;
		around_wall[0]->pos.x = wall->pos.x + 1;
		around_wall[0]->pos.y = wall->pos.y;
		around_wall[0]->add = game->file->texture_ea;
		around_wall[1]->id = wall->id;
		around_wall[1]->a = 1;
		around_wall[1]->b = 0;
		around_wall[1]->c = 1;
		around_wall[1]->d = -(wall->pos.y);
		around_wall[1]->height = 1;
		around_wall[1]->width = 1;
		around_wall[1]->pos.x = wall->pos.x;
		around_wall[1]->pos.y = wall->pos.y;
		around_wall[1]->add = game->file->texture_so;
		around_wall[2]->id = wall->id;
		around_wall[2]->a = 0;
		around_wall[2]->b = 1;
		around_wall[2]->c = 1;
		around_wall[2]->d = -(wall->pos.x + wall->height - 1);
		around_wall[2]->height = 1;
		around_wall[2]->width = 1;
		around_wall[2]->pos.x = wall->pos.x;
		around_wall[2]->pos.y = wall->pos.y + wall->height - 1;
		around_wall[2]->add = game->file->texture_no;
	}
	if (!(lst = ft_lstnew(around_wall[0])))
	{
		free(around_wall[0]);
		free(around_wall[1]);
		free(around_wall[2]);
		return (3);
	}
	ft_lstadd_front(&(game->lst_walls), lst);
	if (!(lst = ft_lstnew(around_wall[1])))
	{
		free(around_wall[0]);
		free(around_wall[1]);
		free(around_wall[2]);
		return (3);
	}
	ft_lstadd_front(&(game->lst_walls), lst);
	if (!(lst = ft_lstnew(around_wall[2])))
	{
		free(around_wall[0]);
		free(around_wall[1]);
		free(around_wall[2]);
		return (3);
	}
	ft_lstadd_front(&(game->lst_walls), lst);
	return (0);
}

static int		ft_create_h_walls(t_game *game, t_plane *plane, char **map, int *id)
{
	t_wall	*wall;
	t_list	*lst;
	int		i;
	int		j;
	t_dot	pos;

	i = 0;
	j = (int)plane->d * -1;
	while (map[j][i])
		if (map[j][i] && map[j][i] == '1')
		{
			pos.x = i;
			pos.y = j;
			if (!(wall = ft_init_wall(game, plane, pos, id)))
				return (3);
			while (map[j][i] && map[j][++i] == '1')
				wall->width++;
			if (!(lst = ft_lstnew(wall)))
			{
				free(wall);
				return (3);
			}
			ft_lstadd_back(&(game->lst_walls), lst);
		}
		else
			while (map[j][i] && map[j][i] != '1')
				i++;
	return (0);
}

static int		ft_create_v_walls(t_game *game, t_plane *plane, char **map, int *id)
{
	t_wall	*wall;
	t_list	*lst;
	int		i;
	int		j;
	t_dot	pos;

	i = 0;
	j = (int)plane->d * -1;
	while (i < ft_count_array(map))
	{
		if (j < (int)ft_strlen(map[i]) && map[i][j] == '1')
		{
			pos.x = j;
			pos.y = i;
			if (!(wall = ft_init_wall(game, plane, pos, id)))
				return (3);
			while (map[i] && j < (int)ft_strlen(map[i]) && map[++i][j] == '1')
				wall->height++;
			if (!(lst = ft_lstnew(wall)))
			{
				free(wall);
				return (3);
			}
			ft_lstadd_back(&(game->lst_walls), lst);
		}
		else
			while (map[++i] && j < (int)ft_strlen(map[i]) && map[i][j] != '1')
				i++;
	}
	return (0);
}

int				ft_create_walls(t_list *lst_planes, t_game *game)
{
	t_plane	*plane;
	t_list	*lst;
	t_wall	*wall;
	int		id;

	id = 0;
	while (lst_planes)
	{
		plane = lst_planes->content;
		if (plane->a == 1)
		{
			if (ft_create_h_walls(game, plane, game->file->map, &id) == 3)
				return (3);
		}
		else if (plane->b == 1)
		{
			if (ft_create_v_walls(game, plane, game->file->map, &id) == 3)
				return (3);
		}
		lst_planes = lst_planes->next;
	}
		lst = game->lst_walls;
		while (lst)
		{
			wall = lst->content;
			if (ft_create_around_wall(game, wall))
				return (3);
			lst = lst->next;
		}
		ft_delete_walls(&(game->lst_walls));
	return (0);
}
