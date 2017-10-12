/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 11:27:41 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/12 10:46:44 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

static int					general_move(t_grid *grid, t_coord const c_zero,
		t_coord const new_c, int const loop, int right_coord, int const move,
		int weight)
{
	t_coord					mem_prev;

	if (grid == NULL || grid->grid == NULL)
		return (-1);
	g_way_good[loop] = move;
	right_coord = new_right_coord(grid, c_zero, new_c, right_coord);
	mem_prev.x = grid->prev.x;
	mem_prev.y = grid->prev.y;
	grid->prev.x = c_zero.x;
	grid->prev.y = c_zero.y;
	grid->grid[c_zero.y][c_zero.x] = grid->grid[new_c.y][new_c.x];
	grid->grid[new_c.y][new_c.x] = EMPTY;
	solve_npuzzle(grid, loop + 1, new_c,
			get_move_possible(grid, new_c), right_coord, weight);
	grid->prev.x = mem_prev.x;
	grid->prev.y = mem_prev.y;
	grid->grid[new_c.y][new_c.x] = grid->grid[c_zero.y][c_zero.x];
	grid->grid[c_zero.y][c_zero.x] = EMPTY;
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
	return (general_move(grid, c_zero, cpy, loop, right_coord, MOVE_TOP,
			weight));
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
	return (general_move(grid, c_zero, cpy, loop, right_coord, MOVE_BOTTOM,
			weight));
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
	return (general_move(grid, c_zero, cpy, loop, right_coord, MOVE_LEFT,
			weight));
}

int							move_right(t_grid *grid, int loop,
		t_coord const c_zero, int const move, int right_coord, int weight)
{
	t_coord					cpy;

	if (grid == NULL || grid->grid == NULL)
		return (-1);
	if ((move & FLAG_RIGHT) == 0)
		return (false);
	cpy.y = c_zero.y;
	cpy.x = c_zero.x + 1;
	return (general_move(grid, c_zero, cpy, loop, right_coord, MOVE_RIGHT,
			weight));
}
