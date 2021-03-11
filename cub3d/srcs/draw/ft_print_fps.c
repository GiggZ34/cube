/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@studen.42lyon.fr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:43:22 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/11 20:21:29 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_print_fps(t_game *game, char *fps)
{
    int     color;
    int     x;

    color = ft_color_generate(255, 0, 0, 0);
    x = game->screen.size / 10;
    if (fps)
    {
        mlx_string_put(game->mlx, game->window, x, 10, color, fps);
        free(fps);
        game->dt.dt_str = NULL;
    }
    return (0);
}
