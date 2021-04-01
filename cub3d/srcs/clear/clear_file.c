/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:01:48 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/01 13:14:23 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_clear_file(t_file *file, int fd)
{
	char	*s;

	s = NULL;
	while (get_next_line(fd, &s) == 1)
			free(s);
	if (s)
		free(s);
	if (file->map)
		ft_free_array(file->map);
	s = NULL;
	file->map = NULL;
}

static void	ft_delete_textures(t_game *game)
{
	if (game->file.texture_ea)
	{
		if (mlx_destroy_image(game->mlx, game->file.texture_ea->ptr))
			printf("Error\nTexture east destruction failed\n");
		free(game->file.texture_ea);
		game->file.texture_ea = NULL;
	}
	if (game->file.texture_no)
	{
		if (mlx_destroy_image(game->mlx, game->file.texture_no->ptr))
			printf("Error\nTexture north destruction failed\n");
		free(game->file.texture_no);
		game->file.texture_no = NULL;
	}
	if (game->file.texture_s)
	{
		if (mlx_destroy_image(game->mlx, game->file.texture_s->ptr))
			printf("Error\nTexture sprite destruction failed\n");
		free(game->file.texture_s);
		game->file.texture_s = NULL;
	}
	if (game->file.texture_so)
	{
		if (mlx_destroy_image(game->mlx, game->file.texture_so->ptr))
			printf("Error\nTexture south destruction failed\n");
		free(game->file.texture_so);
		game->file.texture_so = NULL;
	}
	if (game->file.texture_we)
	{
		if (mlx_destroy_image(game->mlx, game->file.texture_we->ptr))
			printf("Error\nTexture west destruction failed\n");
		free(game->file.texture_we);
		game->file.texture_we = NULL;
	}
	if (game->sky_ground.ground_texture.ptr)
		if (mlx_destroy_image(game->mlx, game->sky_ground.ground_texture.ptr))
			printf("Error\nTexture ground destruction failed\n");
	if (game->sky_ground.sky_texture.ptr)
		if (mlx_destroy_image(game->mlx, game->sky_ground.sky_texture.ptr))
			printf("Error\nTexture sky destruction failed\n");
}

static void	delete(void *content)
{
	free(content);
	content = NULL;
}

static int	ft_free_hud(t_game *g, t_player *p)
{
	int	i;
	int	j;
	int	nb_frame;

	if (p->gun)
	{
		i = -1;
		while (++i < nb_anim)
		{
			nb_frame = ft_define_nb_anim(i);
			j = -1;
			while (++j < nb_frame)
				mlx_destroy_image(g->mlx, p->gun[i][j].ptr);
			free(p->gun[i]);
			p->gun[i] = NULL;
		}
		free(p->gun);
		p->gun = NULL;
	}
	return (0);
}

int			ft_trash_game(t_game *game, t_error_code code, int fd, char *msg)
{
	system("killall afplay");
	ft_error_file(&game->file, code, msg);
	ft_clear_file(&game->file, fd);
	ft_delete_textures(game);
	ft_free_hud(game, &game->player);
	ft_lstclear(&game->file.check_file, &delete, 1);
	ft_lstclear(&game->lst_sprites, &delete, 1);
	ft_lstclear(&game->lst_planes_bottom, &delete, 1);
	ft_lstclear(&game->lst_planes_top, &delete, 1);
	ft_lstclear(&game->lst_planes_left, &delete, 1);
	ft_lstclear(&game->lst_planes_right, &delete, 1);
	ft_lstclear(&game->player.view.sprites_in_fov, &delete, 0);
	if (game->tab_planes.bottom)
	{
		free(game->tab_planes.bottom);
		game->tab_planes.bottom = NULL;
	}
	if (game->tab_planes.top)
	{
		free(game->tab_planes.top);
		game->tab_planes.top = NULL;
	}
	if (game->tab_planes.left)
	{
		free(game->tab_planes.left);
		game->tab_planes.left = NULL;
	}
	if (game->tab_planes.right)
	{
		free(game->tab_planes.right);
		game->tab_planes.right = NULL;
	}
	if (game->screen.ptr)
		mlx_destroy_image(game->mlx, game->screen.ptr);
	if (game->dt.dt_str)
	{
		free(game->dt.dt_str);
		game->dt.dt_str = NULL;
	}
	if (game->dt.scale_str)
	{
		free(game->dt.scale_str);
		game->dt.scale_str = NULL;
	}
	if (game->player.guns.obj_texture.ptr)
		mlx_destroy_image(game->mlx, game->player.guns.obj_texture.ptr);
	if (game->player.view.tab_vectors)
	{
		free(game->player.view.tab_vectors);
		game->player.view.tab_vectors = NULL;
	}
	if (game->window)
	{
		mlx_clear_window(game->mlx, game->window);
		if (mlx_destroy_window(game->mlx, game->window))
			printf("Windows destruction failed\n");
	}
	exit(code);
}
