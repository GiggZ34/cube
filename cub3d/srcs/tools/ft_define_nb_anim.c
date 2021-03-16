/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_define_nb_frame.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:05:23 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/16 15:06:08 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_player_anim	ft_define_nb_anim(int state)
{
	if (state == 0)
		return (anim_rest);
	else if (state == 1)
		return (anim_reload);
	else
		return (anim_shoot);
}
