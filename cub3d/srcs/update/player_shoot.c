/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_shoot.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 17:03:20 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 17:12:00 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	add_shoot_light(t_game *game)
{
	t_light	*l;
	t_light	*new_light;

	new_light = ft_calloc(sizeof(t_light), 1);
	if (!new_light)
		ft_trash_game(game, allocation_fail, -1, "In add_shoot_light");
	new_light->type = 'S';
	new_light->x = game->player.position.x;
	new_light->y = game->player.position.y;
	new_light->z = game->player.position.z - 0.2;
	new_light->rgb[0] = 1;
	new_light->rgb[1] = 1;
	new_light->rgb[2] = 1;
	l = game->light;
	while (l->next)
		l = l->next;
	l->next = new_light;
}

static void	search_shoot_light(t_light *current)
{
	t_light	*previous;
	t_light	*next;

	previous = NULL;
	next = NULL;
	while (current && current->type != 'S')
	{
		previous = current;
		current = current->next;
		next = current->next;
	}
	if (current && current->type == 'S')
	{
		previous->next = next;
		if (current)
			free(current);
	}
}

static void	remove_shoot_light(t_game *game)
{
	t_light	*previous;

	if (game->light)
	{
		previous = game->light;
		if (previous->type == 'S')
		{
			game->light = previous->next;
			free(previous);
		}
		else
			search_shoot_light(previous->next);
	}
}

static void	change_state(t_game *game, t_player *player, int state)
{
	if (state == shoot)
	{
		play_sound("afplay -v 3 ./sounds/shoot_fusil.mp3 &");
		if (game->light)
			add_shoot_light(game);
		player->ammunition--;
	}
	if (state == reload)
	{
		player->ammunition = barel_fusil;
		play_sound("afplay -v 3 ./sounds/reload_fusil.mp3 &");
	}
	player->anim_frame = 0;
	player->state = state;
	player->control.reload = 0;
	player->control.shoot = 0;
}

void	player_shoot(t_game *game, t_player *player)
{
	int	nb_anim;

	if (player->control.shoot && player->state != shoot
		&& player->state != reload && player->ammunition > 0)
		change_state(game, player, shoot);
	else if (player->control.reload == 1 && player->state != reload)
		change_state(game, player, reload);
	else
	{
		if ((player->state != shoot
				|| (player->state == shoot && player->anim_frame))
			&& game->light)
			remove_shoot_light(game);
		player->anim_frame += game->dt.dt * 10;
	}
	nb_anim = ft_define_nb_anim(player->state);
	if ((int)player->anim_frame >= nb_anim)
		change_state(game, player, rest);
	if (player->state == rest && player->ammunition <= 0)
		change_state(game, player, reload);
	player->arm = &player->gun[player->state][(int)player->anim_frame];
}
