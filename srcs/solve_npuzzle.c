/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_npuzzle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 11:01:24 by fpasquer          #+#    #+#             */
/*   Updated: 2017/09/20 11:25:23 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

static t_func_move			g_moves[] =
{
	{FLAG_TOP, move_top},
	{FLAG_BOTTOM, move_bottom},
	{FLAG_LEFT, move_left},
	{FLAG_RIGHT, move_right},
	{FLAG_NONE, NULL}
};

void						solve_npuzzle(t_grid *grid, int loop,
		int const y_zero, int const x_zero, int const move, int right_coord,
		int weight)
{
	static long long int	iteration = 0;
	unsigned int			i;
	t_way_weight			ways[MAX_WAY];

	if (grid == NULL || loop > grid->max_deep || loop >= MAX_DEEP)
		return ;
	if (right_coord == grid->end)
	{
		grid->found = true;
		grid->max_deep = loop - 1;
		printf("number of move = %d\niteration = %lld\n", loop, iteration);
		return ;
	}
	iteration++;
	if (get_order_ways(grid, ways, move, y_zero, x_zero, weight) != true)
		return ;
	for (i = 0; g_moves[i].key != FLAG_NONE && grid->found != true; i++)
		if (ways[i].weight >= 0)
			if (g_moves[ways[i].index].f(grid, loop, y_zero, x_zero, move,
					right_coord, ways[i].weight) < 0)
				return ;
	iteration = (loop == 0) ? 0 : iteration;
}