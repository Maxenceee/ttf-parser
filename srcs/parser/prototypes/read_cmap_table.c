/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cmap_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:27:06 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:24:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

int	push_cmap(t_true_type_font *font, void *ttf)
{
	t_linkedl_mask	*tmp;

	if (!ttf)
		return (FONT_ALLOC_ERROR);
	tmp = font->cmap;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		tmp->next = ttf;
	else
		font->cmap = ttf;
	return (FONT_NO_ERROR);
}

int	read_cmap(t_true_type_font *this, t_binary_reader *file, uint32_t offset)
{
	uint32_t	old;
	uint32_t	format;
	uint32_t	length;

	old = file->seek(file, offset);
	format = file->get_uint16(file);
	length = file->get_uint16(file);
	(void)length;
	file->get_uint16(file);
	if (format == 0)
	{
		if (push_cmap(this, new_ttcmap0(file)))
			return (FONT_ALLOC_ERROR);
	}
	else if (format == 4)
	{
		if (push_cmap(this, new_ttcmap4(file)))
			return (FONT_ALLOC_ERROR);
	}
	file->seek(file, old);
	return (FONT_NO_ERROR);
}

int	read_cmap_table(t_true_type_font *this,
	t_binary_reader *file, uint32_t offset)
{
	int				i;
	uint16_t		number_subtables;
	t_ttcmap_stable	sub;

	file->seek(file, offset);
	file->get_uint16(file);
	number_subtables = file->get_uint16(file);
	i = -1;
	while (++i < number_subtables)
	{
		sub.platform_id = file->get_uint16(file);
		sub.platform_specific_id = file->get_uint16(file);
		sub.offset = file->get_uint32(file);
		if (sub.platform_id == 3 && sub.platform_specific_id <= 1)
		{
			if (read_cmap(this, file, offset + sub.offset))
				return (FONT_ALLOC_ERROR);
		}
	}
	return (FONT_NO_ERROR);
}
