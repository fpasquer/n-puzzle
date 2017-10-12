/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_grid.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fpasquer <fpasquer@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/19 21:13:29 by fpasquer          #+#    #+#             */
/*   Updated: 2017/10/12 13:40:28 by amaindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/npuzzle.h"

bool						generate_grid(void)
{
	return (system("./grid_generator -s 3 > grid") == -1 ? false : true);
}
