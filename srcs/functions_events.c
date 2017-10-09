/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_events.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 10:39:16 by fpasquer          #+#    #+#             */
/*   Updated: 2017/09/20 10:59:01 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

# define TIME_SLEEP 50000
# define EXIT 53

static t_func_move_show		g_move_show[] = 
{
	{MOVE_TOP, show_move_top},
	{MOVE_BOTTOM, show_move_bottom},
	{MOVE_LEFT, show_move_left},
	{MOVE_RIGHT, show_move_right}
};

int							key_hook(int key, void *param)
{
	t_mlx_npuzzle			**f;
	if ((f = (t_mlx_npuzzle **)param) == NULL)
		return (-1);
	if (key == EXIT)
		leave_window(f);
	return (0);
}

int							close_hook(int button, void *param)
{
	int						cpy;
	t_mlx_npuzzle			**f;

	cpy = button;
	if ((f = (t_mlx_npuzzle **)param) == NULL)
		return (-1);
	exit(EXIT_SUCCESS);
	return (true);
}

int							loop_hook(void *param)
{
	static int				i = 0;
	t_mlx_npuzzle			**f;
	clock_t					time;

	if ((f = (t_mlx_npuzzle **)param) == NULL)
		return (-1);
	if (((time = clock()) - (*f)->time) > TIME_SLEEP)
		if (i < (*f)->grid->max_deep)
		{
			g_move_show[g_way_good[i]].f(f);
			(*f)->time = time;
			draw_grid(*f);
			i++;
		}
	return (true);
}