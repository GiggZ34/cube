/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:00:49 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/21 17:35:19 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	ft_define_ratio(double value)
{
	if (!value)
		return (1);
	if (value > 2 || value < -2)
		return (2);
	return (ft_abs(value));
}

void			ft_rotate_player(t_game *g, t_player *p, double x, double y)
{
	double	ratio_x;
	double	ratio_z;

	if (p->control.right || p->control.left)
		ratio_z = 2;
	else
		ratio_z = ft_define_ratio(x);
	if (p->control.up || p->control.down)
		ratio_x = 2;
	else
		ratio_x = ft_define_ratio(y);
	if (p->control.right || x < 0)
	{
		p->angle_z += -ROTATE_SPEED_Z * ratio_z * g->dt.dt;
		ft_rotate_vectors_collides(p,
									-ROTATE_SPEED_Z * ratio_z * g->dt.dt);
	}
	else if (p->control.left || x > 0)
	{
		p->angle_z += ROTATE_SPEED_Z * ratio_z * g->dt.dt;
		ft_rotate_vectors_collides(p,
									ROTATE_SPEED_Z * ratio_z * g->dt.dt);
	}
	if (p->control.up || y > 0)
		p->angle_x += -ROTATE_SPEED_X * ratio_x * g->dt.dt;
	else if (p->control.down || y < 0)
		p->angle_x += ROTATE_SPEED_X * ratio_x * g->dt.dt;
}
