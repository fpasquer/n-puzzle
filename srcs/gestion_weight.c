/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_weight.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 14:19:49 by fpasquer          #+#    #+#             */
/*   Updated: 2017/09/11 14:35:59 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

static int					compar_weight_ways(void const *a_cpy,
		void const *b_cpy)
{
	t_way_weight			*a;
	t_way_weight			*b;

	if ((a = (t_way_weight*)a_cpy) == NULL ||
			(b = (t_way_weight*)b_cpy) == NULL)
	{
		fprintf(stderr, "Error : %s %d\n", __FILE__, __LINE__);
		exit(EXIT_FAILURE);
	}
	if (a->weight > b->weight)
		return (-1);
	return (a->weight == b->weight ? 0 : 1);
}

static int					get_weight_way(t_grid *grid, int const way,
		int const move, int const y_zero, int const x_zero)
{
	int						i;
	t_func_weight			func_weight[] =
	{
		{FLAG_TOP, get_weight_top},
		{FLAG_BOTTOM, get_weight_bottom},
		{FLAG_LEFT, get_weight_left},
		{FLAG_RIGHT, get_weight_right},
		{FLAG_NONE, NULL}
	};

	if (grid == NULL || grid->grid == NULL || (move & way) == 0)
		return (INT_MIN);
	for (i = 0; func_weight[i].key != FLAG_NONE; i++)
		if (way == func_weight[i].key)
			return (func_weight[i].f(grid, y_zero, x_zero));
	return (INT_MIN);
}

int							get_order_ways(t_grid *grid,
	t_way_weight ways[MAX_DEEP], int const move, int const y_zero,
	int const x_zero)
{
	int						i;
	int						order_move[] =
			{FLAG_TOP, FLAG_BOTTOM, FLAG_LEFT, FLAG_RIGHT};
#ifdef DEBUG
	char					name[4][7] = {"Top", "Botton", "left", "right"};
#endif

	if (grid == NULL || ways == NULL)
		return (-1);
	for (i = 0; i < MAX_WAY; i++)
	{
		ways[i].index = i;
		ways[i].way = order_move[i];
		ways[i].weight = get_weight_way(grid, order_move[i], move, y_zero,
				x_zero);
	}
	qsort(ways, MAX_WAY, sizeof(t_way_weight), compar_weight_ways);
#ifdef DEBUG
	for (i = 0; i < MAX_WAY; i++)
	{
		ft_putstr(" ways[");
		ft_putnbr(i);
		ft_putstr("].way = ");
		ft_putstr(name[ways[i].index]);
		ft_putstr(" .weight = ");
		ft_putnbr(ways[i].weight);
		ft_putchar('\n');
	}
#endif
	return (1);
}