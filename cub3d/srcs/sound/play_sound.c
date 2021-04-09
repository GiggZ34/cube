/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 12:22:02 by grivalan          #+#    #+#             */
/*   Updated: 2021/04/05 11:50:29 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	*cmd(void *sys)
{
	t_system_call	*sys_cmd;

	sys_cmd = (t_system_call *)sys;
	system(sys_cmd->cmd);
	pthread_exit(sys_cmd->thread);
}

void	play_sound(const char *cmd_line)
{
	t_system_call	sys;

	sys.cmd = cmd_line;
	pthread_create(&sys.thread, NULL, &cmd, &sys);
	pthread_join(sys.thread, NULL);
}

void	playmusic(t_game *game)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	if (t.tv_sec - game->music.time > SOUND_TIME)
	{
		game->music.time = t.tv_sec;
		play_sound("afplay sounds/ambience.mp3 &");
	}
}
