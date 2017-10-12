/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 11:27:41 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/12 09:35:30 by fpasquer         ###   ########.fr       */
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
		right_coord = g_grid_3x3[new_y][new_x] == grid->grid[new_y][new_x] ?
				right_coord - 1 : right_coord;
		right_coord = g_grid_3x3[y_zero][x_zero] == grid->grid[new_y][new_x] ?
				right_coord + 1 : right_coord;
	}
	else if (grid->x_y == 4)
	{
		right_coord = g_grid_4x4[new_y][new_x] == grid->grid[new_y][new_x] ?
				right_coord - 1 : right_coord;
		right_coord = g_grid_4x4[y_zero][x_zero] == grid->grid[new_y][new_x] ?
				right_coord + 1 : right_coord;
	}
	else if (grid->x_y == 5)
	{
		right_coord = g_grid_5x5[new_y][new_x] == grid->grid[new_y][new_x] ?
				right_coord - 1 : right_coord;
		right_coord = g_grid_5x5[y_zero][x_zero] == grid->grid[new_y][new_x] ?
				right_coord + 1 : right_coord;
	}
	return (right_coord);
}

static int					general_move(t_grid *grid, int const y_zero,
		int const x_zero, t_coord const new_c, int const loop,
		int right_coord, int move, int weight)
{
	int						mem_x_prev;
	int						mem_y_prev;

	if (grid == NULL || grid->grid == NULL)
		return (-1);
	g_way_good[loop] = move;
	right_coord = new_right_coord(grid, y_zero, x_zero, new_c.y, new_c.x,
			right_coord);
	mem_x_prev = grid->prev.y;
	mem_y_prev = grid->prev.y;
	grid->prev.x = x_zero;
	grid->prev.y = y_zero;
	grid->grid[y_zero][x_zero] = grid->grid[new_c.y][new_c.x];
	grid->grid[new_c.y][new_c.x] = EMPTY;
	solve_npuzzle(grid, loop + 1, new_c,
			get_move_possible(grid, new_c.y, new_c.x), right_coord, weight);
	grid->prev.x = mem_x_prev;
	grid->prev.y = mem_y_prev;
	grid->grid[new_c.y][new_c.x] = grid->grid[y_zero][x_zero];
	grid->grid[y_zero][x_zero] = EMPTY;
	return (true);
}

int							move_top(t_grid *grid, int loop,
		t_coord const c_zero, int const move, int right_coord, int weight)
{
	t_coord					cpy;

	if (grid == NULL || grid->grid == NULL)
		return (-1);
	if ((move & FLAG_TOP) == 0)
		return (false);
	cpy.y = c_zero.y - 1;
	cpy.x = c_zero.x;
	return (general_move(grid, c_zero.y, c_zero.x, cpy, loop,
			right_coord, MOVE_TOP, weight));
}

int							move_bottom(t_grid *grid, int loop,
		t_coord const c_zero, int const move, int right_coord, int weight)
{
	t_coord					cpy;

	if (grid == NULL || grid->grid == NULL)
		return (-1);
	if ((move & FLAG_BOTTOM) == 0)
		return (false);
	cpy.y = c_zero.y + 1;
	cpy.x = c_zero.x;
	return (general_move(grid, c_zero.y, c_zero.x, cpy, loop,
			right_coord, MOVE_BOTTOM, weight));
}

int							move_left(t_grid *grid, int loop,
		t_coord const c_zero, int const move, int right_coord, int weight)
{
	t_coord					cpy;

	if (grid == NULL || grid->grid == NULL)
		return (-1);
	if ((move & FLAG_LEFT) == 0)
		return (false);
	cpy.y = c_zero.y;
	cpy.x = c_zero.x - 1;
	return (general_move(grid, c_zero.y, c_zero.x, cpy, loop,
			right_coord, MOVE_LEFT, weight));
}

int							move_right(t_grid *grid, int loop,
		t_coord const c_zero, int const move, int right_coord,int weight)
{
	t_coord					cpy;

	if (grid == NULL || grid->grid == NULL)
		return (-1);
	if ((move & FLAG_RIGHT) == 0)
		return (false);
	cpy.y = c_zero.y;
	cpy.x = c_zero.x + 1;
	return (general_move(grid, c_zero.y, c_zero.x, cpy, loop,
			right_coord, MOVE_RIGHT, weight));
}
