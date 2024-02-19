/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_offset_tables.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 15:44:59 by mgama             #+#    #+#             */
/*   Updated: 2024/02/19 13:24:00 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "font.h"

static uint32_t	calculate_table_checksum(t_true_type_font *this,
	t_binary_reader *file, uint32_t offset, uint32_t length)
{
	uint32_t	old;
	uint32_t	sum;
	uint32_t	nlongs;

	(void)this;
	old = file->seek(file, offset);
	sum = 0;
	nlongs = ((length + 3) / 4) | 0;
	while (nlongs--)
		sum = (sum + (file->get_uint32(file) & 0xffffffff)) >> 0;
	file->seek(file, old);
	return (sum);
}

int	parse_ttf_tables(t_true_type_font *this,
	t_binary_reader *file, uint32_t len)
{
	uint32_t	i;

	this->tables = malloc(len * sizeof(t_ttf_table));
	if (!this->tables)
		return (ft_error(FONT_ALLOC_ERROR_MSG), FONT_ALLOC_ERROR);
	i = -1;
	while (++i < len)
	{
		this->tables[i] = (t_ttf_table){
			.tag = file->get_string(file, 4),
			.checksum = file->get_uint32(file),
			.offset = file->get_uint32(file),
			.length = file->get_uint32(file)};
		if (!this->tables[i].tag)
			return (ft_error(FONT_ALLOC_ERROR_MSG), FONT_ALLOC_ERROR);
		if (ft_strcmp("head", this->tables[i].tag)
			&& calculate_table_checksum(this, file, this->tables[i].offset,
				this->tables[i].length) != this->tables[i].checksum)
			return (ft_error(FONT_ERROR_PREFIX"Invalid checksum in font.\n"),
				FONT_ERROR);
	}
	return (FONT_NO_ERROR);
}

int	read_offset_tables(t_true_type_font *this, t_binary_reader *file)
{
	this->props.scalar_type = file->get_uint32(file);
	this->props.num_tables = file->get_uint16(file);
	this->props.search_range = file->get_uint16(file);
	this->props.entry_selector = file->get_uint16(file);
	this->props.range_shift = file->get_uint16(file);
	if (parse_ttf_tables(this, file, this->props.num_tables))
		return (FONT_ERROR);
	return (FONT_NO_ERROR);
}
