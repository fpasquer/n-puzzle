/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 10:28:12 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/12 10:28:55 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

int							new_right_coord(t_grid *grid, t_coord const c_zero,
		t_coord const new_c, int right_coord)
{
	if (grid == NULL || grid->grid == NULL)
		return (right_coord);
	if (grid->x_y == 3)
	{
		right_coord = g_grid_3x3[new_c.y][new_c.x] ==
				grid->grid[new_c.y][new_c.x] ? right_coord - 1 : right_coord;
		right_coord = g_grid_3x3[c_zero.y][c_zero.x] ==
				grid->grid[new_c.y][new_c.x] ? right_coord + 1 : right_coord;
	}
	else if (grid->x_y == 4)
	{
		right_coord = g_grid_4x4[new_c.y][new_c.x] ==
				grid->grid[new_c.y][new_c.x] ? right_coord - 1 : right_coord;
		right_coord = g_grid_4x4[c_zero.y][c_zero.x] ==
				grid->grid[new_c.y][new_c.x] ? right_coord + 1 : right_coord;
	}
	else if (grid->x_y == 5)
	{
		right_coord = g_grid_5x5[new_c.y][new_c.x] ==
				grid->grid[new_c.y][new_c.x] ? right_coord - 1 : right_coord;
		right_coord = g_grid_5x5[c_zero.y][c_zero.x] ==
				grid->grid[new_c.y][new_c.x] ? right_coord + 1 : right_coord;
	}
	return (right_coord);
}
