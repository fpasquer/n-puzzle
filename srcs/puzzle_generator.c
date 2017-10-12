/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_generator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:43:57 by amaindro          #+#    #+#             */
/*   Updated: 2017/10/12 13:54:15 by amaindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/puzzle_generator.h"

void	change_increment(int cond1, int cond2, int *x1, int *y1)
{
	if (cond1)
	{
		*y1 = *x1;
		*x1 = 0;
	}
	else if (cond2)
	{
		*x1 = -*y1;
		*y1 = 0;
	}
}

int		*puzzle_filler(int *puzzle, int s, int x[], int y[])
{
	int		cur;

	cur = 1;
	while (1)
	{
		puzzle[x[0] + y[0] * s] = cur;
		if (cur == 0)
			break ;
		cur++;
		change_increment((x[0] + x[1] == s || x[0] + x[1] < 0 ||
				(x[1] != 0 && puzzle[x[0] + x[1] + y[0] * s] != -1)),
				(y[0] + y[1] == s || y[0] + y[1] < 0 ||
				(y[1] != 0 && puzzle[x[0] + (y[1] + y[0]) * s] != -1)),
				&x[1], &y[1]);
		x[0] += x[1];
		y[0] += y[1];
		if (cur == s * s)
			cur = 0;
	}
	return (puzzle);
}

int		*puzzle_generator(int s)
{
	int		*puzzle;
	int		x[2];
	int		y[2];

	if (!(puzzle = ft_memalloc(sizeof(int) * s * s)))
		return (NULL);
	x[0] = 0;
	while (x[0] < s * s)
		puzzle[x[0]++] = -1;
	x[0] = 0;
	x[1] = 1;
	y[0] = 0;
	y[1] = 0;
	return (puzzle_filler(puzzle, s, x, y));
}

void	print_grid(int size, int solvable)
{
	int		x;
	int		y;
	int		*puzzle;

	srand(getpid());
	puzzle = puzzle_generator(size);
	x = -1;
	y = rand() % 10000 * size;
	while (++x < y)
		puzzle_swapper(size, puzzle);
	make_solvable_or_not(size, solvable, puzzle);
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
			printf("%*d ", (int)ft_nblen(size * size), puzzle[y * size + x++]);
		printf("\n");
		y++;
	}
	ft_memdel((void**)&puzzle);
}

int		main(int ac, char **av)
{
	int		size;
	int		i;
	int		solvable;

	srand(getpid());
	if (ac == 2 || ac == 3)
	{
		i = 0;
		size = 0;
		solvable = rand() % 2;
		while (++i < ac)
		{
			if (ft_is_number(av[i]))
				size = ft_atoi(av[i]);
			if (ft_strcmp(av[i], "-u") == 0)
				solvable = 1;
			if (ft_strcmp(av[i], "-s") == 0)
				solvable = 2;
		}
		if (size >= 3)
			print_grid(size, solvable);
	}
}
