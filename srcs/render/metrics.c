/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   metrics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 18:59:52 by mgama             #+#    #+#             */
/*   Updated: 2024/02/19 13:59:01 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

t_hor_metrics	get_horizontal_metrics(t_true_type_font *this, uint16_t glyph_index)
{
	uint32_t	offset;
	uint32_t	old;
	uint16_t	advance_width;
	int16_t		left_side_bearing;

	offset = get_table_offset(this, "hmtx");
	old = this->file->seek(this->file, offset + 4);
	if (glyph_index < this->props.num_of_long_hor_metrics)
	{
		offset += glyph_index * 4;
		old = this->file->seek(this->file, offset);
		advance_width = this->file->get_uint16(this->file);
		left_side_bearing = this->file->get_int16(this->file);
	}
	else
	{
		old = this->file->seek(this->file, offset
				+ (this->props.num_of_long_hor_metrics - 1) * 4);
		advance_width = this->file->get_uint16(this->file);
		this->file->seek(this->file, offset
			+ this->props.num_of_long_hor_metrics * 4
			+ 2 * (glyph_index - this->props.num_of_long_hor_metrics));
		left_side_bearing = this->file->get_fword(this->file);
	}
	this->file->seek(this->file, old);
	return ((t_hor_metrics){.advance_width = advance_width,
		.left_side_bearing = left_side_bearing});
}
