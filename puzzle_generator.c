/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_generator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 11:43:57 by amaindro          #+#    #+#             */
/*   Updated: 2017/10/11 16:52:37 by amaindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int		*puzzle_swapper(int s, int *puzzle)
{
	int		pos0;
	int		chozen_switch;
	int		rand1;
	int		rand2;

	pos0 = 0;
	while (pos0 < s * s && puzzle[pos0] != 0)
		pos0++;
	rand1 = -1;
	if (pos0 % s > 0 && rand1 < (rand2 = rand()))
	{
		chozen_switch = pos0 - 1;
		rand1 = rand2;
	}
	if (pos0 % s < s - 1 && rand1 < (rand2 = rand()))
	{
		chozen_switch = pos0 + 1;
		rand1 = rand2;
	}
	if (pos0 / s > 0 && rand1 < (rand2 = rand()))
	{
		chozen_switch = pos0 - s;
		rand1 = rand2;
	}
	if (pos0 / s < s - 1 && rand1 < (rand2 = rand()))
		chozen_switch = pos0 + s;
	puzzle[pos0] = puzzle[chozen_switch];
	puzzle[chozen_switch] = 0;
	return (puzzle);
}

int		*puzzle_generator(int s)
{
	int		*puzzle;
	int		cur;
	int		x[2];
	int		y[2];

	if (!(puzzle = ft_memalloc(sizeof(int) * s * s)))
		return (NULL);
	x[0] = 0;
	while (x[0] < s * s)
		puzzle[x[0]++] = -1;
	cur = 1;
	x[0] = 0;
	x[1] = 1;
	y[0] = 0;
	y[1] = 0;
	while (1)
	{
		puzzle[x[0] + y[0] * s] = cur;
		if (cur == 0)
			break ;
		cur++;
		if (x[0] + x[1] == s || x[0] + x[1] < 0 ||
				(x[1] != 0 && puzzle[x[0] + x[1] + y[0] * s] != -1))
		{
			y[1] = x[1];
			x[1] = 0;
		}
		else if (y[0] + y[1] == s || y[0] + y[1] < 0 ||
				(y[1] != 0 && puzzle[x[0] + (y[1] + y[0]) * s] != -1))
		{
			x[1] = -y[1];
			y[1] = 0;
		}
		x[0] += x[1];
		y[0] += y[1];
		if (cur == s * s)
			cur = 0;
	}
	return (puzzle);
}

int		*make_solvable_or_not(int size, int solvable, int *puzzle)
{
	int		tmp;

	if (solvable == 1)
	{
		printf("# This puzzle is unsolvable\n%d\n", size);
		if (puzzle[0] == 0 || puzzle[1] == 0)
		{
			tmp = puzzle[size * size - 1];
			puzzle[size * size - 1] = puzzle[size * size - 2];
			puzzle[size * size - 2] = tmp;
		}
		else
		{
			tmp = puzzle[0];
			puzzle[0] = puzzle[1];
			puzzle[1] = tmp;
		}
	}
	else
		printf("# This puzzle is solvable\n%d\n", size);
	return (puzzle);
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
