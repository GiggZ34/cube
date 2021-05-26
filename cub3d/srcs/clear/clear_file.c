/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/11 15:01:48 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/26 12:31:22 by grivalan         ###   ########lyon.fr   */
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

static void	free_texture_lst(t_game *game)
{
	t_texture	*t;

	while (game->file.texture_obj)
	{
		t = game->file.texture_obj;
		free(t->type);
		game->file.texture_obj = t->next;
		free(t);
	}
}

static void	ft_delete_textures(t_game *game)
{
	game->file.texture_ea = free_texture(game, game->file.texture_ea);
	game->file.texture_no = free_texture(game, game->file.texture_no);
	game->file.texture_s = free_texture(game, game->file.texture_s);
	game->file.texture_so = free_texture(game, game->file.texture_so);
	game->file.texture_we = free_texture(game, game->file.texture_we);
	if (game->sky_ground.ground_texture.ptr)
		if (mlx_destroy_image(game->mlx, game->sky_ground.ground_texture.ptr))
			printf("Error\nTexture destruction failed\n");
	if (game->sky_ground.sky_texture.ptr)
		if (mlx_destroy_image(game->mlx, game->sky_ground.sky_texture.ptr))
			printf("Error\nTexture destruction failed\n");
	if (game->player.guns.obj_texture.ptr)
		if (mlx_destroy_image(game->mlx, game->player.guns.obj_texture.ptr))
			printf("Error\nTexture destruction failed\n");
}

static void	free_allocation_cub(t_game *game)
{
	game->tab_planes.bottom = free_with_protect(game->tab_planes.bottom);
	game->tab_planes.top = free_with_protect(game->tab_planes.top);
	game->tab_planes.left = free_with_protect(game->tab_planes.left);
	game->tab_planes.right = free_with_protect(game->tab_planes.right);
	game->dt.dt_str = free_with_protect(game->dt.dt_str);
	game->dt.scale_str = free_with_protect(game->dt.scale_str);
	game->player.view.tab_vectors
		= free_with_protect(game->player.view.tab_vectors);
}

int	ft_trash_game(t_game *game, t_error_code code, int fd, char *msg)
{
	system("killall afplay");
	ft_error_file(code, msg);
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
	free_allocation_cub(game);
	free_texture_lst(game);
	if (game->screen.ptr)
		mlx_destroy_image(game->mlx, game->screen.ptr);
	clear_light(game);
	if (game->window)
	{
		mlx_clear_window(game->mlx, game->window);
		if (mlx_destroy_window(game->mlx, game->window))
			printf("Windows destruction failed\n");
	}
	exit(code);
}
