/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 11:27:41 by fpasquer          #+#    #+#             */
/*   Updated: 2017/09/11 15:30:47 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

static int					new_right_coord(t_grid *grid, int const y_zero,
	int const x_zero, int const new_y, int const new_x, int right_coord)
{
	if (grid == NULL || grid->grid == NULL)
		return (right_coord);
	if (grid->x_y == 3)
	{
		right_coord = g_grid_3x3[y_zero][x_zero] == EMPTY ? right_coord - 1 : right_coord;
		right_coord = g_grid_3x3[new_y][new_x] == grid->grid[new_y][new_x] ? right_coord - 1 : right_coord;
		right_coord = g_grid_3x3[y_zero][x_zero] == grid->grid[new_y][new_x] ? right_coord + 1 : right_coord;
		right_coord = g_grid_3x3[new_y][new_x] == EMPTY ? right_coord + 1 : right_coord;
	}
	return (right_coord);
}

static int					general_move(t_grid *grid, int const y_zero,
		int const x_zero, int const new_y, int const new_x, int const loop,
		int right_coord, int move)
{
	int						mem_x_prev;
	int						mem_y_prev;

	if (grid == NULL || grid->grid == NULL)
		return (-1);
	g_way_move[loop] = move;
	right_coord = new_right_coord(grid, y_zero, x_zero, new_y, new_x, right_coord);
	mem_x_prev = grid->prev.y;
	mem_y_prev = grid->prev.y;
	grid->prev.x = x_zero;
	grid->prev.y = y_zero;
	grid->grid[y_zero][x_zero] = grid->grid[new_y][new_x];
	grid->grid[new_y][new_x] = EMPTY;
	solve_npuzzle(grid, loop + 1, new_y, new_x,
		get_move_possible(grid, new_y, new_x), right_coord);
	grid->prev.x = mem_x_prev;
	grid->prev.y = mem_y_prev;
	grid->grid[new_y][new_x] = grid->grid[y_zero][x_zero];
	grid->grid[y_zero][x_zero] = EMPTY;
	return (true);
}

int							move_top(t_grid *grid, int loop,
		int const y_zero, int const x_zero, int const move, int right_coord)
{
	if (grid == NULL || grid->grid == NULL)
		return (-1);
	if ((move & FLAG_TOP) == 0)
		return (false);
	return (general_move(grid, y_zero, x_zero, y_zero - 1, x_zero, loop,
			right_coord, MOVE_TOP));
	
}

int							move_bottom(t_grid *grid, int loop,
	int const y_zero, int const x_zero, int const move, int right_coord)
{
if (grid == NULL || grid->grid == NULL)
		return (-1);
	if ((move & FLAG_BOTTOM) == 0)
		return (false);
	return (general_move(grid, y_zero, x_zero, y_zero + 1, x_zero, loop,
			right_coord, MOVE_BOTTOM));
}

int							move_left(t_grid *grid, int loop,
	int const y_zero, int const x_zero, int const move, int right_coord)
{
	if (grid == NULL || grid->grid == NULL)
		return (-1);
	if ((move & FLAG_LEFT) == 0)
		return (false);
	return (general_move(grid, y_zero, x_zero, y_zero, x_zero - 1, loop,
			right_coord, MOVE_LEFT));
}

int							move_right(t_grid *grid, int loop,
	int const y_zero, int const x_zero, int const move, int right_coord)
{
	if (grid == NULL || grid->grid == NULL)
		return (-1);
	if ((move & FLAG_RIGHT) == 0)
		return (false);
	return (general_move(grid, y_zero, x_zero, y_zero, x_zero + 1, loop,
			right_coord, MOVE_RIGHT));
}