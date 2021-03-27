/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_fps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grivalan <grivalan@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 20:43:22 by grivalan          #+#    #+#             */
/*   Updated: 2021/03/26 19:34:51 by grivalan         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_print_fps(t_game *game, char *fps, char *scale)
{
    int     color;
    int     x;
    char    *str;

    color = ft_color_generate(255, 0, 0, 0);
    x = game->screen.size / 10;
    if (fps && scale)
    {
        str = ft_strjoin("FPS   | ", fps);
        if (!str)
            return (ft_trash_game(game, allocation_fail, -1, "Fuction ft_print_fps | line 25\n"));
        mlx_string_put(game->mlx, game->window, x, 10, color, str);
		free(str);
        str = ft_strjoin("SCALE | ", scale);
        if (!str)
            return (ft_trash_game(game, allocation_fail, -1, "Fuction ft_print_fps | line 30\n"));
        mlx_string_put(game->mlx, game->window, x, 20, color, str);
        free(str);
        free(fps);
        free(scale);
        game->dt.dt_str = NULL;
        game->dt.scale_str = NULL;
    }
    return (0);
}
