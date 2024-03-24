/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glyph_count.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 12:16:32 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:24:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

uint16_t	glyph_count(t_true_type_font *this)
{
	uint32_t	old;
	uint16_t	count;

	old = this->file->seek(this->file, get_table_offset(this, "maxp") + 4);
	count = this->file->get_uint16(this->file);
	this->file->seek(this->file, old);
	return (count);
}
