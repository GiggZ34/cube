/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:00:49 by grivalan          #+#    #+#             */
/*   Updated: 2021/05/22 17:20:35 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	ft_define_ratio(int control, double value)
{
	if (control)
		return (2);
	if (!value)
		return (1);
	if (value < 2 && value > -2)
		return (0);
	else if (value > 5 || value < -5)
		return (4);
	return (ft_abs(value));
}

void	ft_rotate_player(t_game *g, t_player *p, double x, double y)
{
	double	ratio_x;
	double	ratio_z;

	ratio_z = ft_define_ratio(p->control.right || p->control.left, x);
	ratio_x = ft_define_ratio(p->control.up || p->control.down, y);
	if (p->control.right || x < 0)
	{
		p->angle_z += -ROTATE_SPEED * ratio_z * g->dt.dt;
		ft_rotate_vectors_collides(p,
			-ROTATE_SPEED * ratio_z * g->dt.dt);
	}
	else if (p->control.left || x > 0)
	{
		p->angle_z += ROTATE_SPEED * ratio_z * g->dt.dt;
		ft_rotate_vectors_collides(p,
			ROTATE_SPEED * ratio_z * g->dt.dt);
	}
	if ((p->control.up || y > 0) && p->angle_x < M_PI / 3)
		p->angle_x += ROTATE_SPEED * ratio_x * g->dt.dt;
	else if ((p->control.down || y < 0) && p->angle_x > -M_PI / 3)
		p->angle_x += -ROTATE_SPEED * ratio_x * g->dt.dt;
	p->control.mouse_x = p->control.mouse_x_pos;
	p->control.mouse_y = p->control.mouse_y_pos;
}
