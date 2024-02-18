/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_hhea_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 00:30:06 by mgama             #+#    #+#             */
/*   Updated: 2024/01/02 12:53:13 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

int	read_hhea_table(t_true_type_font *this,
	t_binary_reader *file, uint32_t offset)
{
	file->seek(file, offset);
	file->get_fixed(file);
	this->props.ascent = file->get_fword(file);
	this->props.descent = file->get_fword(file);
	this->props.line_gap = file->get_fword(file);
	this->props.advance_width_max = file->get_uint16(file);
	this->props.min_left_side_bearing = file->get_fword(file);
	this->props.min_right_side_bearing = file->get_fword(file);
	this->props.x_max_extent = file->get_fword(file);
	this->props.caret_slope_rise = file->get_int16(file);
	this->props.caret_slope_run = file->get_int16(file);
	this->props.caret_offset = file->get_int16(file);
	file->get_int16(file);
	file->get_int16(file);
	file->get_int16(file);
	file->get_int16(file);
	this->props.metric_data_format = file->get_int16(file);
	this->props.num_of_long_hor_metrics = file->get_uint16(file);
	return (FONT_NO_ERROR);
}
