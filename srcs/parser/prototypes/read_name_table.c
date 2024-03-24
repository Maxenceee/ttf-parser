/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_name_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/22 20:38:35 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 20:09:50 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

/**
 * FIXME:
 * Both get_string and get_unicode_string are called for some field
 * is the same name_id is called more than one time free the last allocation.
 * 
 */

int	read_name_table_platform(t_true_type_font *this, t_binary_reader *file,
	uint32_t table_offset, uint32_t string_offset)
{
	uint16_t	platform_id;
	uint16_t	name_id;
	uint16_t	length;
	uint16_t	offset;
	uint32_t	old;
	char		*name;

	platform_id = file->get_uint16(file);
	file->get_uint16(file);
	file->get_uint16(file);
	name_id = file->get_uint16(file);
	length = file->get_uint16(file);
	offset = file->get_uint16(file);
	old = file->seek(file, table_offset + string_offset + offset);
	if (platform_id == 0 || platform_id == 3)
		name = file->get_unicode_string(file, length);
	else
		name = file->get_string(file, length);
	if (!name)
		return (ft_error(FONT_ALLOC_ERROR_MSG), FONT_ALLOC_ERROR);
	file->seek(file, old);
	if (name_id == 1)
	{
		if (this->family.font_family)
			free(this->family.font_family);
		this->family.font_family = name;
	}
	else if (name_id == 2)
	{
		if (this->family.font_sub_family)
			free(this->family.font_sub_family);
		this->family.font_sub_family = name;
	}
	else if (name_id == 4)
	{
		if (this->family.full_name)
			free(this->family.full_name);
		this->family.full_name = name;
	}
	else if (name_id == 6)
	{
		if (this->family.postscript_name)
			free(this->family.postscript_name);
		this->family.postscript_name = name;
	}
	else
		free(name);
	return (FONT_NO_ERROR);
}

int	read_name_table(t_true_type_font *this,
	t_binary_reader *file, uint32_t offset)
{
	int			i;
	uint16_t	count;
	uint16_t	string_offset;

	i = -1;
	file->seek(file, offset);
	this->family.format = file->get_uint16(file);
	count = file->get_uint16(file);
	string_offset = file->get_uint16(file);
	while (++i < count)
		read_name_table_platform(this, file, offset, string_offset);
	return (FONT_NO_ERROR);
}
