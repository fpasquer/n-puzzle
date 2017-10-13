/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solvable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/10 09:10:59 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/13 09:12:24 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

#define MAXDIM 6

static bool					soluble(int nc, int nl, int *jeu)
{
	int						i;
	int						p_zero;
	int						n;
	int						n_permut;
	int						copie[MAXDIM * MAXDIM];

	i = -1;
	n = nc * nl - 1;
	while (++i <= n)
		if ((copie[i] = jeu[i]) == 0)
			p_zero = i;
	n_permut = (n - p_zero) % nc + (n - p_zero) / nc;
	while (n > 0)
	{
		if (n != p_zero)
		{
			copie[p_zero] = copie[n];
			p_zero = n;
			n_permut++;
		}
		while (copie[--p_zero] != n)
			;
		n--;
	}
	return (n_permut % 2 == nc % 2 ? true : false);
}

bool						solvable(t_grid *grid)
{
	bool					ret;
	int						y;
	int						x;
	int						i;
	int						*grid_tab;

	if (grid == NULL || grid->grid == NULL)
		return (false);
	if ((grid_tab = ft_memalloc(sizeof(int) * (grid->x_y * grid->x_y))) == NULL)
		return (false);
	i = 0;
	y = 0;
	while (y < grid->x_y)
	{
		x = 0;
		while (x < grid->x_y)
			grid_tab[i++] = grid->grid[y][x++];
		y++;
	}
	ret = soluble(grid->x_y, grid->x_y, grid_tab);
	ft_memdel((void**)&grid_tab);
	grid->found = ret == false ? true : grid->found;
	printf("La grille est %s\n", ret == true ? "Solvable" : "Insolvable");
	return (ret);
}
