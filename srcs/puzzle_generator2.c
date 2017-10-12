/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puzzle_generator2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/12 13:44:47 by amaindro          #+#    #+#             */
/*   Updated: 2017/10/12 13:54:01 by amaindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/puzzle_generator.h"

void	choose_switch(int cond, int *chozen_switch, int *rand1, int pos)
{
	int		rand2;

	if (cond && *rand1 < (rand2 = rand()))
	{
		*chozen_switch = pos;
		*rand1 = rand2;
	}
}

int		*puzzle_swapper(int s, int *puzzle)
{
	int		pos0;
	int		chozen_switch;
	int		rand1;

	pos0 = 0;
	while (pos0 < s * s && puzzle[pos0] != 0)
		pos0++;
	rand1 = -1;
	choose_switch((pos0 % s > 0), &chozen_switch, &rand1, pos0 - 1);
	choose_switch((pos0 % s < s - 1), &chozen_switch, &rand1, pos0 + 1);
	choose_switch((pos0 / s > 0), &chozen_switch, &rand1, pos0 - s);
	choose_switch((pos0 / s < s - 1), &chozen_switch, &rand1, pos0 + s);
	puzzle[pos0] = puzzle[chozen_switch];
	puzzle[chozen_switch] = 0;
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
