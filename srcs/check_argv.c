/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:32:11 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/12 16:12:19 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

static int					is_error(char const *str)
{
	if (str != NULL)
		ft_putstr_fd(str, STDERR_FILENO);
	return (-1);
}

static int					check_argv_next(char *path)
{
	int						fd;
	char					*name_file;

	if (path == NULL && generate_grid() == false)
		return (is_error("Error grid"));
	name_file = (path == NULL) ? DEFAULT_FILE : path;
	if ((fd = ft_fopen(name_file, "r")) <= 0)
		return (is_error("Path missing"));
	if (ft_is_dir(name_file) == true)
	{
		close(fd);
		return (is_error("Path is a directory"));
	}
	return (fd);
}

int							check_argv(char **path, int *flags)
{
	int						i;

	if (path == NULL || flags == NULL)
		return (is_error("Path empty"));
	*flags = FLAG_NONE;
	i = 0;
	while (path[++i] != NULL)
	{
		if (ft_strcmp(path[i], "-manhattan") == 0)
			*flags = *flags ^ F_MANHATTAN;
		else if (ft_strcmp(path[i], "-mal_place") == 0)
			*flags = *flags ^ F_MAL_PLACE;
		else if (ft_strcmp(path[i], "-linear_c") == 0)
			*flags = *flags ^ F_LINEAR_C;
		else if (ft_strcmp(path[i], "-tile_out") == 0)
			*flags = *flags ^ F_TILE_OUT;
		else
			break ;
	}
	return (check_argv_next(path[i]));
}
