/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rotate_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:00:49 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/30 19:09:37 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	ft_define_ratio(double value)
{
	if (!value)
		return (1);
	if (value > 4 || value < -4)
		return (2);
	return (ft_abs(value));
}

void			ft_rotate_player(t_game *g, t_player *p, double x, double y)
{
	double	ratio_x;
	double	ratio_z;

	printf("%f || %f - %d ** %d\n", x, y, p->control.mouse_x_pos, p->control.mouse_y_pos);
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
	if ((p->control.up || y > 0) && p->angle_x > -M_PI / 2)
		p->angle_x += -ROTATE_SPEED * ratio_x * g->dt.dt;
	else if ((p->control.down || y < 0) && p->angle_x < M_PI / 2)
		p->angle_x += ROTATE_SPEED * ratio_x * g->dt.dt;
	p->control.mouse_x = p->control.mouse_x_pos;
	p->control.mouse_y = p->control.mouse_y_pos;
}
