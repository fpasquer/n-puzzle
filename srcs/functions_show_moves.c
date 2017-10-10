/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_show_moves.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/02 09:56:02 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/10 15:12:25 by fpasquer         ###   ########.fr       */
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
	return (1);
}
