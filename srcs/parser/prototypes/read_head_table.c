/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_head_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:05:02 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:24:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

int	read_head_table(t_true_type_font *this,
	t_binary_reader *file, uint32_t offset)
{
	file->seek(file, offset);
	this->props.version = file->get_fixed(file);
	this->props.font_revision = file->get_fixed(file);
	this->props.checksum_adjustment = file->get_uint32(file);
	this->props.magic_number = file->get_uint32(file);
	if (this->props.magic_number != 0x5f0f3cf5)
		return (ft_error(FONT_ERROR_PREFIX"Magic number error.\n"), FONT_ERROR);
	this->props.flags = file->get_uint16(file);
	this->props.units_per_em = file->get_uint16(file);
	this->props.created = file->get_date(file);
	this->props.modified = file->get_date(file);
	this->props.x_min = file->get_fword(file);
	this->props.y_min = file->get_fword(file);
	this->props.x_max = file->get_fword(file);
	this->props.y_max = file->get_fword(file);
	this->props.mac_style = file->get_uint16(file);
	this->props.lowest_rec_ppem = file->get_uint16(file);
	this->props.font_direction_hint = file->get_int16(file);
	this->props.index_to_loc_format = file->get_int16(file);
	this->props.glyph_data_format = file->get_int16(file);
	return (FONT_NO_ERROR);
}
