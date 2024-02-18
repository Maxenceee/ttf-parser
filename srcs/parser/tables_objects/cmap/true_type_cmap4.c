/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_type_cmap4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:55:40 by mgama             #+#    #+#             */
/*   Updated: 2024/01/12 16:59:57 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

void	get_segments_data(t_binary_reader *file, t_ttcmap4 *cmap)
{
	uint16_t	rg;
	int			i;

	i = -1;
	while (++i < cmap->seg_count)
		cmap->segments[i].end_code = file->get_uint16(file);
	file->get_uint16(file);
	i = -1;
	while (++i < cmap->seg_count)
		cmap->segments[i].start_code = file->get_uint16(file);
	i = -1;
	while (++i < cmap->seg_count)
		cmap->segments[i].id_delta = file->get_uint16(file);
	i = -1;
	while (++i < cmap->seg_count)
	{
		rg = file->get_uint16(file);
		if (rg)
			cmap->segments[i].id_range_offset = file->tell(file) - 2 + rg;
		else
			cmap->segments[i].id_range_offset = 0;
	}
}

t_ttcmap4	*new_ttcmap4(t_binary_reader *file)
{
	t_ttcmap4	*cmap;

	if (!file)
		return (NULL);
	cmap = (t_ttcmap4 *)ft_calloc(1, sizeof(t_ttcmap4));
	if (!cmap)
		return (ft_error(FONT_ALLOC_ERROR_MSG), NULL);
	cmap->format = 4;
	cmap->file = file;
	cmap->map = &true_type_cmap4_map;
	cmap->seg_count = file->get_uint16(file) / 2;
	file->get_uint16(file);
	file->get_uint16(file);
	file->get_uint16(file);
	cmap->segments = malloc(cmap->seg_count * sizeof(t_ttcmap4_segment));
	if (!cmap->segments)
		return (ft_error(FONT_ALLOC_ERROR_MSG), free(cmap), NULL);
	get_segments_data(file, cmap);
	return (cmap);
}
