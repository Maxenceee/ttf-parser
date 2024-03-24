/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_glyph_offset.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 12:26:28 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:24:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

uint32_t	get_glyph_offset(t_true_type_font *this, uint16_t index)
{
	uint32_t	table_off;
	uint32_t	offset;
	uint32_t	old;

	table_off = get_table_offset(this, "loca");
	if (this->props.index_to_loc_format == 1)
	{
		old = this->file->seek(this->file, table_off + index * 4);
		offset = this->file->get_uint32(this->file);
	}
	else
	{
		old = this->file->seek(this->file, table_off + index * 2);
		offset = this->file->get_uint16(this->file) * 2;
	}
	this->file->seek(this->file, old);
	return (offset + get_table_offset(this, "glyf"));
}
