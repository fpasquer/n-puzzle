/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/28 17:32:11 by fpasquer          #+#    #+#             */
/*   Updated: 2017/09/09 12:02:33 by fpasquer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

static int					is_error(char const *str)
{
	if (str != NULL)
		ft_putstr_fd(str, STDERR_FILENO);
	return (-1);
}

int							check_argv(char **path, int *flags)
{
	int						fd;
	int						i;

	if (path == NULL || flags == NULL)
		return (is_error("Path empty"));
	for (fd = -1, i = 1, *flags = FLAG_NONE; path[i] != NULL; i++)
	{
		if (ft_strcmp(path[i], "-manhattan") == 0)
			*flags = *flags ^ F_MANHATTAN;
		else if (ft_strcmp(path[i] ,"-mal_place") == 0)
			*flags = *flags ^ F_MAL_PLACE;
		else
			break ;
	}
	if ((fd = ft_fopen(path[i], "r")) <= 0)
		return (is_error("Path missing"));
	if (ft_is_dir(path[i]) == true)
	{
		close(fd);
		return (is_error("Path is a directory"));
	}
	return (fd);
}