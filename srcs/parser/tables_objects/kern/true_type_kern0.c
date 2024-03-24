/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_type_kern0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 01:10:18 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:24:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

static int	fill_kern_block(t_binary_reader *file, t_ttkern0 *kern)
{
	int			i;
	uint16_t	left;
	uint16_t	right;
	int16_t		value;

	i = -1;
	kern->map = malloc(kern->n_pairs * sizeof(t_ttkern0_map));
	if (!kern->map)
		return (FONT_ALLOC_ERROR);
	while (++i < kern->n_pairs)
	{
		left = file->get_uint16(file);
		right = file->get_uint16(file);
		value = file->get_fword(file);
		kern->map[i].key = (left << 16) | right;
		kern->map[i].value = value;
	}
	kern->reset = &true_type_kern0_reset;
	kern->get = &true_type_kern0_get;
	kern->reset(kern);
	return (FONT_NO_ERROR);
}

t_ttkern0	*new_ttkern0(t_binary_reader *file,
	uint16_t vertical, uint16_t cross)
{
	t_ttkern0	*kern;

	if (!file)
		return (NULL);
	kern = (t_ttkern0 *)ft_calloc(1, sizeof(t_ttkern0));
	if (!kern)
		return (NULL);
	kern->file = file;
	kern->swap = (vertical && !cross) || (!vertical && cross);
	kern->offset = file->tell(file);
	kern->n_pairs = file->get_uint16(file);
	file->get_uint16(file);
	file->get_uint16(file);
	file->get_uint16(file);
	if (fill_kern_block(file, kern))
		return (free(kern), NULL);
	return (kern);
}
