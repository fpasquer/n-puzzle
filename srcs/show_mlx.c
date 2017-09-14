/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 10:09:15 by fpasquer          #+#    #+#             */
/*   Updated: 2017/09/03 22:28:15 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../incs/npuzzle.h"

/*void						show_way(t_grid *grid)
{
	static char	const		rep[4][7] = {"TOP", "BOTTOM", "LEFT", "RIGHT"};
	int						i;

	if (grid != NULL)
	{
		if (grid->found == true)
			for(i = 0; i < grid->max_deep; i++)
				printf("vay[%3d] = %7s\n", i, rep[g_way_good[i]]);
		else
			printf("Pas trouve\n");
	}
}*/

static t_mlx_npuzzle		*init_mlx(t_grid *grid)
{
	int						i;
	t_mlx_npuzzle			*mlx;

	if (grid == NULL || (mlx = ft_memalloc(sizeof(*mlx))) == NULL)
		return (NULL);
	if ((mlx->mlx = mlx_init()) == NULL)
		return (NULL);
	if ((mlx->win = mlx_new_window(mlx->mlx, NB_PIX_EACH_BOX * grid->x_y,
			NB_PIX_EACH_BOX * grid->x_y, "N-puzzle")) == NULL)
		return (NULL);
	if ((mlx->img = ft_memalloc(sizeof(*mlx->img) * grid->x_y * grid->x_y)) == NULL)
		return (NULL);
	for (i = 0; i < grid->x_y * grid->x_y; i++)
		if ((mlx->img[i] = mlx_new_image(mlx->mlx, NB_PIX_EACH_BOX ,
				NB_PIX_EACH_BOX)) == NULL)
			break ;
	if ((mlx->data = ft_memalloc(sizeof(*mlx->data) * grid->x_y * grid->x_y)) == NULL)
		return (NULL);
	for (i = 0; i < grid->x_y * grid->x_y; i++)
		if ((mlx->data[i] = (int*)mlx_get_data_addr(mlx->img[i], &mlx->t[0],
				&mlx->t[1], &mlx->t[2])) == NULL)
			break;
	return (mlx);
}

void						show_way(t_grid *grid, char ***file, int fd,
		int const y_zero, int const x_zero)
{
	
	t_mlx_npuzzle			*mlx;

	if (grid == NULL || (mlx = ft_memalloc(sizeof(*mlx))) == NULL)
		return ;
	if (grid->found == true)
	{
		// static char	const		rep[4][7] = {"TOP", "BOTTOM", "LEFT", "RIGHT"};
		// for (int i = 0; i < grid->max_deep; i++)
		// 	printf("way[%2d] = %s\n", i, rep[g_way_good[i]]);
		if ((mlx = init_mlx(grid)) == NULL)
			return ;
		mlx->grid = grid;
		mlx->file = file;
		mlx->fd = fd;
		mlx->y_zero = y_zero;
		mlx->x_zero = x_zero;
		draw_grid(mlx);
		mlx_loop_hook(mlx->mlx, loop_hook, &mlx);
		mlx_key_hook(mlx->win, key_hook, &mlx);
		mlx_hook(mlx->win, 17, 0, close_hook, &mlx);
		mlx_loop(mlx->mlx);


	}
	else
		printf("Pas trouve\n");
}

void						leave_window(t_mlx_npuzzle **mlx)
{
	int						i;

	if (mlx == NULL || (*mlx) == NULL || (*mlx)->mlx == NULL)
		return ;
	if ((*mlx)->img != NULL)
	{
		for (i = 0; i < (*mlx)->grid->x_y * (*mlx)->grid->x_y; i++)
			if ((*mlx)->img[i] != NULL)
				mlx_destroy_image((*mlx)->mlx, (*mlx)->img[i]);
		ft_memdel((void**)&(*mlx)->img);
	}
	if ((*mlx)->data != NULL)
		ft_memdel((void**)&(*mlx)->data);
	if ((*mlx)->win != NULL)
		mlx_destroy_window((*mlx)->mlx, (*mlx)->win);
	del_grid(&(*mlx)->grid);
	del_file((*mlx)->file);
	close((*mlx)->fd);
	ft_memdel((void**)mlx);
	exit(EXIT_SUCCESS);
}