/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_kern_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/27 19:33:04 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:24:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

int	push_kern(t_true_type_font *font, void *ttf)
{
	t_linkedl_mask	*tmp;

	if (!ttf)
		return (FONT_ALLOC_ERROR);
	tmp = font->kern;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		tmp->next = ttf;
	else
		font->kern = ttf;
	return (FONT_NO_ERROR);
}

int	read_kern_table(t_true_type_font *this,
	t_binary_reader *file, uint32_t offset)
{
	int			i;
	uint16_t	n_tables;
	uint16_t	length;
	uint16_t	coverage;

	file->seek(file, offset);
	file->get_uint16(file);
	n_tables = file->get_uint16(file);
	i = -1;
	while (++i < n_tables)
	{
		file->get_uint16(file);
		length = file->get_uint16(file);
		coverage = file->get_uint16(file);
		if ((coverage >> 8) == 0)
		{
			if (push_kern(this, new_ttkern0(file, (coverage & 0x1) == 0, (coverage & 4) != 0)))
				return (FONT_ALLOC_ERROR);
		}
		else
			file->seek(file, file->tell(file) + length);
	}
	return (FONT_NO_ERROR);
}
