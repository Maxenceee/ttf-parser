/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_type_cmap0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:55:42 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:24:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

t_ttcmap0	*new_ttcmap0(t_binary_reader *file)
{
	int			i;
	t_ttcmap0	*cmap;

	if (!file)
		return (NULL);
	cmap = (t_ttcmap0 *)ft_calloc(1, sizeof(t_ttcmap0));
	if (!cmap)
		return (ft_error(FONT_ALLOC_ERROR_MSG), NULL);
	cmap->file = file;
	cmap->glyph_indexes = (uint8_t *)ft_calloc(256, sizeof(uint8_t));
	if (!cmap->glyph_indexes)
		return (ft_error(FONT_ALLOC_ERROR_MSG), free(cmap), NULL);
	i = -1;
	while (++i < 256)
		cmap->glyph_indexes[i] = file->get_uint8(file);
	cmap->map = &true_type_cmap0_map;
	return (cmap);
}
