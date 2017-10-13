/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve_npuzzle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 11:01:24 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/13 09:47:33 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

static t_func_move			g_moves[] =
{
	{FLAG_TOP, move_top, "Haut"},
	{FLAG_BOTTOM, move_bottom, "Bas"},
	{FLAG_LEFT, move_left, "Gauche"},
	{FLAG_RIGHT, move_right, "Right"},
	{FLAG_NONE, NULL, "\n"}
};

void						solve_npuzzle(t_grid *grid, int loop,
		t_coord const c_zero, int const move, int right_coord, int weight)
{
	static long long int	iteration = 0;
	unsigned int			i;
	t_way_weight			ways[MAX_WAY];

																				if (iteration == 5)
																					exit(10);
																				for (int k = 0; k < grid->x_y; k++)
																				{
																					for (int l = 0; l < grid->x_y; l++)
																						printf("%3d", grid->grid[k][l]);
																					printf("\n");
																				}
	if (grid == NULL || loop > grid->max_deep)
		return ;
	if (right_coord == grid->end)
	{
		grid->found = true;
		grid->max_deep = loop - 1;
		printf("number of move = %d\niteration = %lld\n", loop, iteration);
		return ;
	}
	iteration++;
	if (get_order_ways(grid, ways, move, c_zero, weight) != true)
		return ;
	i = 0;
	while (g_moves[i].key != FLAG_NONE && grid->found != true)
		if (ways[i++].weight >= 0)
			if (g_moves[ways[i - 1].index].f(grid, loop, c_zero,
					move, right_coord, ways[i - 1].weight) < 0)
				return ;
	iteration = (loop == 0) ? 0 : iteration;
}
