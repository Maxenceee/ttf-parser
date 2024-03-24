/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   true_type_cmap4_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgama <mgama@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 11:25:24 by mgama             #+#    #+#             */
/*   Updated: 2024/03/24 18:24:11 by mgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "_font.h"

t_ttcmap4_cache	*new_cache(uint8_t key, uint16_t glyph_index)
{
	t_ttcmap4_cache	*c;

	c = ft_calloc(1, sizeof(t_ttcmap4_cache));
	if (!c)
		return (NULL);
	c->key = key;
	c->glyph_index = glyph_index;
	return (c);
}

int	push_to_chaches(t_ttcmap4 *this, t_ttcmap4_cache *cache)
{
	t_ttcmap4_cache	*tmp;

	if (!cache)
		return (FONT_ALLOC_ERROR);
	tmp = this->caches;
	while (tmp)
	{
		if (!tmp->next)
			break ;
		tmp = tmp->next;
	}
	if (tmp)
		tmp->next = cache;
	else
		this->caches = cache;
	return (FONT_NO_ERROR);
}

int	get_chache(t_ttcmap4 *this, uint8_t key)
{
	t_ttcmap4_cache	*tmp;

	tmp = this->caches;
	while (tmp)
	{
		if (tmp->key == key)
			return (tmp->glyph_index);
		tmp = tmp->next;
	}
	return (0);
}

static uint16_t	true_type_cmap4_map_index(t_ttcmap4 *this,
	t_ttcmap4_segment seg, uint8_t char_code)
{
	uint32_t	glyph_index_addr;
	uint16_t	index;

	if (seg.id_range_offset)
	{
		glyph_index_addr = seg.id_range_offset + 2
			* (char_code - seg.start_code);
		this->file->seek(this->file, glyph_index_addr);
		index = this->file->get_uint16(this->file);
	}
	else
		index = (seg.id_delta + char_code) & 0xffff;
	return (index);
}

uint16_t	true_type_cmap4_map(t_ttcmap4 *this, uint8_t char_code)
{
	int					i;
	t_ttcmap4_segment	seg;
	uint16_t			index;

	i = -1;
	while (!get_chache(this, char_code) && ++i < this->seg_count)
	{
		seg = this->segments[i];
		if (seg.start_code <= char_code && seg.end_code >= char_code)
		{
			index = true_type_cmap4_map_index(this, seg, char_code);
			push_to_chaches(this, new_cache(char_code, index));
			break ;
		}
		if (i == this->seg_count)
			push_to_chaches(this, new_cache(char_code, 0));
	}
	return (get_chache(this, char_code));
}
