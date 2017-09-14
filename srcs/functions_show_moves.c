/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_show_moves.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 09:56:02 by fpasquer          #+#    #+#             */
/*   Updated: 2017/09/03 16:47:18 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

int							show_move_top(t_mlx_npuzzle **mlx)
{
	if (mlx == NULL || *mlx == NULL || (*mlx)->grid == NULL ||
			(*mlx)->grid->grid == NULL)
		return (-1);
	printf("%s\n", __FUNCTION__);
	(*mlx)->grid->grid[(*mlx)->y_zero][(*mlx)->x_zero] =
			(*mlx)->grid->grid[(*mlx)->y_zero - 1][(*mlx)->x_zero];
	(*mlx)->grid->grid[(*mlx)->y_zero - 1][(*mlx)->x_zero] = EMPTY;
	(*mlx)->y_zero--;
//	print_grid((*mlx)->grid, 1, MOVE_TOP);
	return (1);
}

int							show_move_bottom(t_mlx_npuzzle **mlx)
{
	if (mlx == NULL || *mlx == NULL || (*mlx)->grid == NULL ||
			(*mlx)->grid->grid == NULL)
		return (-1);
	printf("%s\n", __FUNCTION__);
	(*mlx)->grid->grid[(*mlx)->y_zero][(*mlx)->x_zero] =
			(*mlx)->grid->grid[(*mlx)->y_zero + 1][(*mlx)->x_zero];
	(*mlx)->grid->grid[(*mlx)->y_zero + 1][(*mlx)->x_zero] = EMPTY;
	(*mlx)->y_zero++;
//	print_grid((*mlx)->grid, 1, MOVE_BOTTOM);
	return (1);
}

int							show_move_left(t_mlx_npuzzle **mlx)
{
	if (mlx == NULL || *mlx == NULL || (*mlx)->grid == NULL ||
			(*mlx)->grid->grid == NULL)
		return (-1);
	printf("%s\n", __FUNCTION__);
	(*mlx)->grid->grid[(*mlx)->y_zero][(*mlx)->x_zero] =
			(*mlx)->grid->grid[(*mlx)->y_zero][(*mlx)->x_zero - 1];
	(*mlx)->grid->grid[(*mlx)->y_zero][(*mlx)->x_zero - 1] = EMPTY;
	(*mlx)->x_zero--;
//	print_grid((*mlx)->grid, 0, MOVE_LEFT);
	return (1);
}

int							show_move_right(t_mlx_npuzzle **mlx)
{
	if (mlx == NULL || *mlx == NULL || (*mlx)->grid == NULL ||
			(*mlx)->grid->grid == NULL)
		return (-1);
	printf("%s\n", __FUNCTION__);
	(*mlx)->grid->grid[(*mlx)->y_zero][(*mlx)->x_zero] =
			(*mlx)->grid->grid[(*mlx)->y_zero][(*mlx)->x_zero + 1];
	(*mlx)->grid->grid[(*mlx)->y_zero][(*mlx)->x_zero + 1] = EMPTY;
	(*mlx)->x_zero++;
//	print_grid((*mlx)->grid, 0, MOVE_RIGHT);
	return (1);
}